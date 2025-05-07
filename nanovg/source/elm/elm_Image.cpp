#include "elm/elm_Image.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace elm::ui {

Image Image::New(NVGcontext *vg, float posX, float posY,
                 float width, float height, const char *imagePath,
                 float angle, float alpha) {
    return Image(vg, posX, posY, width, height, imagePath, angle, alpha);
}

Image::Image(NVGcontext *vg, float posX, float posY,
             float width, float height, const char *imagePath,
             float angle, float alpha)
    : vg(vg), posX(posX), posY(posY), width(width), height(height), imagePath(imagePath), angle(angle), alpha(alpha) {
    drawImage();
}

Image::~Image() {
    if (vg && loadImage)
        nvgDeleteImage(vg, loadImage);
}

void Image::drawImage() {
    loadImage = nvgCreateImage(vg, imagePath, 0);
    if (loadImage == 0) {
        printf("Error loading image: %s\n", imagePath);
        return;
    }

    NVGpaint imgPaint = nvgImagePattern(vg, posX, posY, width, height, angle, loadImage, alpha);
    nvgBeginPath(vg);
    nvgRect(vg, posX, posY, width, height);
    nvgFillPaint(vg, imgPaint);
    nvgFill(vg);
}

void Image::update() { drawImage(); }

} // namespace elm::ui