#include "elm/elm_Commons.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace elm::commons {

// Construtor
Commons::Commons(NVGcontext *vg) : vg(vg) {
    loadImagesFromRomfs();
}

// Destrutor
Commons::~Commons() {
    if (vg)
        destroyImages();
}

// Carrega as imagens do romfs
void Commons::loadImagesFromRomfs() {
    loadImages[0] = nvgCreateImage(vg, "romfs:/images/image1.jpg", 0);
    loadImages[1] = nvgCreateImage(vg, "romfs:/images/image2.png", 0);

    if (loadImages[0] == 0 || loadImages[1] == 0) {
        printf("Erro ao carregar imagens.\n");
    }
}

// Libera as imagens
void Commons::destroyImages() {
    for (int i = 0; i < 2; i++) {
        if (loadImages[i] != 0) {
            nvgDeleteImage(vg, loadImages[i]);
        }
    }
}

// Desenha um rótulo simples
void Commons::drawLabel(const char *text, float x, float y, float w, float h) {
    NVG_NOTUSED(w);

    nvgFontSize(vg, 64.0f);
    nvgFontFace(vg, "sans");
    nvgFillColor(vg, nvgRGBA(0, 0, 0, 128));

    nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
    nvgText(vg, x, y + h * 0.5f, text, NULL);
}

// Desenha um retângulo com texto e imagens
void Commons::drawTextInRect(const char *text, float x, float y, float w, float h) {
    float img1Size = 100.0f;
    float img2Size = 80.0f;

    // Desenha o retângulo de fundo
    nvgBeginPath(vg);
    nvgRect(vg, x, y, w, h);
    nvgFillColor(vg, nvgRGBA(0, 0, 0, 255));
    nvgFill(vg);

    // Desenha a primeira imagem (120x120)
    float img1OffsetX = x + 20;
    float img1OffsetY = y - 25;
    NVGpaint img1Paint = nvgImagePattern(vg, img1OffsetX, img1OffsetY, img1Size, img1Size, 0, loadImages[0], 1.0f);
    nvgBeginPath(vg);
    nvgRect(vg, img1OffsetX, img1OffsetY, img1Size, img1Size);
    nvgFillPaint(vg, img1Paint);
    nvgFill(vg);

    // Desenha a segunda imagem (80x80) centralizada no canto inferior direito da primeira
    float img2OffsetX = img1OffsetX + img1Size - img2Size / 2.0f;
    float img2OffsetY = img1OffsetY + img1Size - img2Size / 2.0f;
    NVGpaint img2Paint = nvgImagePattern(vg, img2OffsetX, img2OffsetY, img2Size, img2Size, 0, loadImages[1], 1.0f);
    nvgBeginPath(vg);
    nvgRect(vg, img2OffsetX, img2OffsetY, img2Size, img2Size);
    nvgFillPaint(vg, img2Paint);
    nvgFill(vg);

    // Configura o estilo do texto
    nvgFontSize(vg, 16.0f);
    nvgFontFace(vg, "sans");
    nvgFillColor(vg, nvgRGBA(255, 255, 255, 255));
    nvgTextAlign(vg, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

    // Desenha o texto no centro do retângulo
    nvgText(vg, 220, y + h / 2, text, NULL);
}

} // namespace elm::commons