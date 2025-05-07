#include "elm/elm_Rectangle.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace elm::ui {
Rectangle Rectangle::New(NVGcontext *vg, float posX, float posY, float width, float height, NVGcolor rectangleColor) {
    return Rectangle(vg, posX, posY, width, height, rectangleColor);
}

Rectangle::Rectangle(NVGcontext *vg, float posX, float posY, float width, float height, NVGcolor rectangleColor)
    : vg(vg), posX(posX), posY(posY), width(width), height(height), rectangleColor(rectangleColor) {
    drawRectangle();
}

Rectangle::~Rectangle() {}

void Rectangle::drawRectangle() {
    nvgBeginPath(vg);
    nvgRect(vg, posX, posY, width, height);
    nvgFillColor(vg, rectangleColor);
    nvgFill(vg);
}

void Rectangle::updateRectangle() { drawRectangle(); }
} // namespace elm::ui