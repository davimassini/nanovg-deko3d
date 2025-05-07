#include "elm/elm_Text.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace elm::ui {

Text Text::New(NVGcontext *vg, const char *text,
               const char *fontFace, int fontSize,
               float x, float y, NVGcolor textColor, int textAlign) {
    return Text(vg, text, fontFace, fontSize, x, y, textColor, textAlign);
}

Text::Text(NVGcontext *vg, const char *text,
           const char *fontFace, int fontSize,
           float x, float y, NVGcolor textColor, int textAlign)
    : vg(vg), text(text), fontFace(fontFace), fontSize(fontSize), x(x), y(y), textColor(textColor), textAlign(textAlign) {
    drawText();
}

Text::~Text() {}

void Text::drawText() {
    nvgFontSize(vg, fontSize);
    nvgFontFace(vg, fontFace);
    nvgFillColor(vg, textColor);
    nvgTextAlign(vg, textAlign);
    nvgText(vg, x, y, text, NULL);
}

void Text::update() {
    drawText();
}

const char *Text::getText() const { return this->text; }
const char *Text::getFontFace() const { return this->fontFace; }
int Text::getFontSize() const { return this->fontSize; }
float Text::getX() const { return this->x; }
float Text::getY() const { return this->y; }
NVGcolor Text::getTextColor() const { return this->textColor; }
int Text::getTextAlign() const { return this->textAlign; }

void Text::setText(const char *newText) { this->text = newText; }
void Text::setFontFace(const char *newFontFace) { this->fontFace = newFontFace; }
void Text::setFontSize(int newFontSize) { this->fontSize = newFontSize; }
void Text::setX(float newX) { this->x = newX; }
void Text::setY(float newY) { this->y = newY; }
void Text::setTextColor(NVGcolor newColor) { this->textColor = newColor; }
void Text::setTextAlign(int newAlign) { this->textAlign = newAlign; }

} // namespace elm::ui