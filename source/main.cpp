#include <nanovg/framework/CApplication.h>
#include <nanovg/framework/CMemPool.h>

#include <array>
#include <optional>
#include <unistd.h>

#include "elm/elm_Commons.hpp"
#include "nanovg.h"
#include "nanovg_dk.h"

// #define USE_OPENGL
#ifndef USE_OPENGL

#define DEBUG_NXLINK
#ifdef DEBUG_NXLINK
static int nxlink_sock = -1;
#endif

extern "C" void userAppInit(void) {
    Result res = romfsInit();
    if (R_FAILED(res))
        fatalThrow(res);

#ifdef DEBUG_NXLINK
    socketInitializeDefault();
    nxlink_sock = nxlinkStdioForDebug();
#endif
}

extern "C" void userAppExit(void) {
#ifdef DEBUG_NXLINK
    if (nxlink_sock != -1)
        close(nxlink_sock);
    socketExit();
#endif

    romfsExit();
}

void OutputDkDebug(void *userData, const char *context, DkResult result, const char *message) {
    printf("Context: %s\nResult: %d\nMessage: %s\n", context, result, message);
}

class DkTest final : public CApplication {
    static constexpr unsigned NumFramebuffers = 2;
    static constexpr uint32_t FramebufferWidth = 1280;
    static constexpr uint32_t FramebufferHeight = 720;
    static constexpr unsigned StaticCmdSize = 0x1000;

    dk::UniqueDevice device;
    dk::UniqueQueue queue;

    std::optional<CMemPool> pool_images;
    std::optional<CMemPool> pool_code;
    std::optional<CMemPool> pool_data;

    dk::UniqueCmdBuf cmdbuf;

    CMemPool::Handle depthBuffer_mem;
    CMemPool::Handle framebuffers_mem[NumFramebuffers];

    dk::Image depthBuffer;
    dk::Image framebuffers[NumFramebuffers];
    DkCmdList framebuffer_cmdlists[NumFramebuffers];
    dk::UniqueSwapchain swapchain;

    DkCmdList render_cmdlist;

    std::optional<nvg::DkRenderer> renderer;
    NVGcontext *vg;

    int loadImages[2];
    float prevTime;
    PadState pad;

    bool showText = false; // Variável para controlar a visibilidade do texto
    float textStartTime = 0.0f; // Tempo em que o texto começou a ser exibido

    std::unique_ptr<elm::commons::Commons> commons;

public:
    DkTest() {
        device = dk::DeviceMaker{}.setCbDebug(OutputDkDebug).create();
        queue = dk::QueueMaker{device}.setFlags(DkQueueFlags_Graphics).create();

        pool_images.emplace(device, DkMemBlockFlags_GpuCached | DkMemBlockFlags_Image, 16 * 1024 * 1024);
        pool_code.emplace(device, DkMemBlockFlags_CpuUncached | DkMemBlockFlags_GpuCached | DkMemBlockFlags_Code, 128 * 1024);
        pool_data.emplace(device, DkMemBlockFlags_CpuUncached | DkMemBlockFlags_GpuCached, 1 * 1024 * 1024);

        cmdbuf = dk::CmdBufMaker{device}.create();
        CMemPool::Handle cmdmem = pool_data->allocate(StaticCmdSize);
        cmdbuf.addMemory(cmdmem.getMemBlock(), cmdmem.getOffset(), cmdmem.getSize());

        createFramebufferResources();

        this->renderer.emplace(FramebufferWidth, FramebufferHeight, this->device, this->queue, *this->pool_images, *this->pool_code, *this->pool_data);
        this->vg = nvgCreateDk(&*this->renderer, NVG_ANTIALIAS | NVG_STENCIL_STROKES);

        nvgCreateFont(vg, "sans", "romfs:/fonts/Roboto-Regular.ttf");
        
        // Inicializa commons dinamicamente
        commons = std::make_unique<elm::commons::Commons>(vg);

        padConfigureInput(1, HidNpadStyleSet_NpadStandard);
        padInitializeDefault(&pad);
    }

    ~DkTest() {
        destroyFramebufferResources();

        commons.reset();

        nvgDeleteDk(vg);
        this->renderer.reset();
    }

    void createFramebufferResources() {
        dk::ImageLayout layout_depthbuffer;
        dk::ImageLayoutMaker{device}
            .setFlags(DkImageFlags_UsageRender | DkImageFlags_HwCompression)
            .setFormat(DkImageFormat_S8)
            .setDimensions(FramebufferWidth, FramebufferHeight)
            .initialize(layout_depthbuffer);

        depthBuffer_mem = pool_images->allocate(layout_depthbuffer.getSize(), layout_depthbuffer.getAlignment());
        depthBuffer.initialize(layout_depthbuffer, depthBuffer_mem.getMemBlock(), depthBuffer_mem.getOffset());

        dk::ImageLayout layout_framebuffer;
        dk::ImageLayoutMaker{device}
            .setFlags(DkImageFlags_UsageRender | DkImageFlags_UsagePresent | DkImageFlags_HwCompression)
            .setFormat(DkImageFormat_RGBA8_Unorm)
            .setDimensions(FramebufferWidth, FramebufferHeight)
            .initialize(layout_framebuffer);

        std::array<DkImage const *, NumFramebuffers> fb_array;
        uint64_t fb_size = layout_framebuffer.getSize();
        uint32_t fb_align = layout_framebuffer.getAlignment();
        for (unsigned i = 0; i < NumFramebuffers; i++) {
            framebuffers_mem[i] = pool_images->allocate(fb_size, fb_align);
            framebuffers[i].initialize(layout_framebuffer, framebuffers_mem[i].getMemBlock(), framebuffers_mem[i].getOffset());

            dk::ImageView colorTarget{framebuffers[i]}, depthTarget{depthBuffer};
            cmdbuf.bindRenderTargets(&colorTarget, &depthTarget);
            framebuffer_cmdlists[i] = cmdbuf.finishList();

            fb_array[i] = &framebuffers[i];
        }
        swapchain = dk::SwapchainMaker{device, nwindowGetDefault(), fb_array}.create();

        recordStaticCommands();
    }

    void destroyFramebufferResources() {
        if (!swapchain)
            return;

        queue.waitIdle();
        cmdbuf.clear();
        swapchain.destroy();

        for (unsigned i = 0; i < NumFramebuffers; i++) {
            framebuffers_mem[i].destroy();
        }
        depthBuffer_mem.destroy();
    }

    void recordStaticCommands() {
        dk::RasterizerState rasterizerState;
        dk::ColorState colorState;
        dk::ColorWriteState colorWriteState;
        dk::BlendState blendState;

        cmdbuf.setViewports(0, {{0.0f, 0.0f, FramebufferWidth, FramebufferHeight, 0.0f, 1.0f}});
        cmdbuf.setScissors(0, {{0, 0, FramebufferWidth, FramebufferHeight}});

        cmdbuf.clearColor(0, DkColorMask_RGBA, 1.0f, 1.0f, 1.0f, 1.0f);
        cmdbuf.clearDepthStencil(true, 1.0f, 0xFF, 0);

        cmdbuf.bindRasterizerState(rasterizerState);
        cmdbuf.bindColorState(colorState);
        cmdbuf.bindColorWriteState(colorWriteState);

        render_cmdlist = cmdbuf.finishList();
    }

    void render(u64 ns, int keyPressed) {
        if (keyPressed) {
            showText = true; // Ativa a exibição do texto
            textStartTime = ns / 1000000000.0f; // Armazena o tempo atual em segundos
        }

        float time = ns / 1000000000.0;
        float dt = time - prevTime;
        prevTime = time;

        int slot = queue.acquireImage(swapchain);
        queue.submitCommands(framebuffer_cmdlists[slot]);
        queue.submitCommands(render_cmdlist);

        nvgBeginFrame(vg, FramebufferWidth, FramebufferHeight, 1.0f);
        {
            if (showText && (time - textStartTime <= 5.0f)) {
                commons->drawTextInRect("Teste de texto.", 0, 100, 400, 75);
            } else if (showText && (time - textStartTime > 5.0f)) {
                showText = false;
            }
        }
        nvgEndFrame(vg);

        queue.presentImage(swapchain, slot);
    }

    bool onFrame(u64 ns) override {
        padUpdate(&pad);
        u64 kDown = padGetButtonsDown(&pad);
        if (kDown & HidNpadButton_Plus)
            return false;

        render(ns, kDown & HidNpadButton_ZR);
        return true;
    }
};

int main(int argc, char *argv[]) {
    DkTest app;
    app.run();
    return 0;
}
#endif