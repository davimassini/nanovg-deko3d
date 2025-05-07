#ifndef ELM_COMMONS_HPP
#define ELM_COMMONS_HPP

#include "nanovg.h"

namespace elm::commons {

class Commons {
public:
    // Construtor e destrutor
    Commons(NVGcontext* vg);
    ~Commons();

    // Métodos públicos
    void drawLabel(const char* text, float x, float y, float w, float h);
    void drawTextInRect(const char* text, float x, float y, float w, float h);

private:
    NVGcontext* vg;
    int loadImages[2];

    // Métodos auxiliares
    void loadImagesFromRomfs();
    void destroyImages();
};

} // namespace elm::commons

#endif // ELM_COMMONS_HPP