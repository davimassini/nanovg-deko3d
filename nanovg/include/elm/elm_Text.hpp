/**
 * Daydream library
 * @file elm_Text.hpp
 * @author daviMassini
 * @copyright NanoVG for Deko3D (Adubbz) - daviMassini
 */

#ifndef ELM_TEXT_HPP
#define ELM_TEXT_HPP

#include "nanovg.h"

namespace elm::ui {
/**
 * @class Text
 * @brief A class for rendering and managing text using NanoVG.
 *
 * The Text class provides functionality to create, render, and manage text
 * objects with various properties such as font face, font size, position,
 * dimensions, color, and alignment.
 */
class Text {
public:
    /**
     * @brief Creates a new Text object.
     * @param vg Pointer to the NanoVG context.
     * @param text The text string to render.
     * @param fontFace The font face to use for the text.
     * @param fontSize The size of the font.
     * @param x The x-coordinate of the text's position.
     * @param y The y-coordinate of the text's position.
     * @param textColor The color of the text.
     * @param textAlign The alignment of the text (e.g., left, center, right).
     * @return A new Text object.
     */
    static Text New(NVGcontext *vg, const char *text, const char *fontFace, int fontSize, float x, float y, NVGcolor textColor, int textAlign);

    /**
     * @brief Constructs a Text object.
     * @param vg Pointer to the NanoVG context.
     * @param text The text string to render.
     * @param fontFace The font face to use for the text.
     * @param fontSize The size of the font.
     * @param x The x-coordinate of the text's position.
     * @param y The y-coordinate of the text's position.
     * @param textColor The color of the text.
     * @param textAlign The alignment of the text (e.g., left, center, right).
     */
    Text(NVGcontext *vg, const char *text, const char *fontFace, int fontSize, float x, float y, NVGcolor textColor, int textAlign);

    /**
     * @brief Destructor for the Text object.
     */
    ~Text();

    /**
     * @brief Draws the text on the screen.
     */
    void drawText();

    /**
     * @brief Updates the text properties or state.
     */
    void update();

    /**
     * @brief Gets the current text string.
     * @return The text string.
     */
    const char *getText() const;

    /**
     * @brief Gets the current font face.
     * @return The font face string.
     */
    const char *getFontFace() const;

    /**
     * @brief Gets the current font size.
     * @return The font size.
     */
    int getFontSize() const;

    /**
     * @brief Gets the x-coordinate of the text's position.
     * @return The x-coordinate.
     */
    float getX() const;

    /**
     * @brief Gets the y-coordinate of the text's position.
     * @return The y-coordinate.
     */
    float getY() const;

    /**
     * @brief Gets the current text color.
     * @return The text color.
     */
    NVGcolor getTextColor() const;

    /**
     * @brief Gets the current text alignment.
     * @return The text alignment.
     */
    int getTextAlign() const;

    /**
     * @brief Sets a new text string.
     * @param newText The new text string.
     */
    void setText(const char *newText);

    /**
     * @brief Sets a new font face.
     * @param newFontFace The new font face string.
     */
    void setFontFace(const char *newFontFace);

    /**
     * @brief Sets a new font size.
     * @param newFontSize The new font size.
     */
    void setFontSize(int newFontSize);

    /**
     * @brief Sets a new x-coordinate for the text's position.
     * @param newX The new x-coordinate.
     */
    void setX(float newX);

    /**
     * @brief Sets a new y-coordinate for the text's position.
     * @param newY The new y-coordinate.
     */
    void setY(float newY);

    /**
     * @brief Sets a new text color.
     * @param newColor The new text color.
     */
    void setTextColor(NVGcolor newColor);

    /**
     * @brief Sets a new text alignment.
     * @param newAlign The new text alignment.
     */
    void setTextAlign(int newAlign);

private:
    NVGcontext *vg;
    const char *text;
    const char *fontFace;
    int fontSize;
    float x;
    float y;
    NVGcolor textColor;
    int textAlign;
};

} // namespace elm::ui
#endif