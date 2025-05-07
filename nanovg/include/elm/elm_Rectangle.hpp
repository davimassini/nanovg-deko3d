/**
 * Daydream library
 * @file elm_Rectangle.hpp
 * @author daviMassini
 * @copyright NanoVG for Deko3D (Adubbz) - daviMassini
 */

#ifndef ELM_RECTANGLE_HPP
#define ELM_RECTANGLE_HPP

#include "nanovg.h"

namespace elm::ui {

/**
 * @class Rectangle
 * @brief Represents a rectangle UI element with customizable properties such as position, size, color, and text.
 */
class Rectangle {
public:
    /**
     * @brief Creates a new Rectangle instance.
     * @param vg Pointer to the NVGcontext used for rendering.
     * @param posX X-coordinate of the rectangle's position.
     * @param posY Y-coordinate of the rectangle's position.
     * @param width Width of the rectangle.
     * @param height Height of the rectangle.
     * @param rectangleColor Color of the rectangle (default is light gray).
     * @return A new Rectangle instance.
     */
    static Rectangle New(NVGcontext *vg, float posX, float posY, float width, float height, NVGcolor rectangleColor = nvgRGBA(240, 240, 240, 255));

    /**
     * @brief Constructs a Rectangle object.
     * @param vg Pointer to the NVGcontext used for rendering.
     * @param posX X-coordinate of the rectangle's position.
     * @param posY Y-coordinate of the rectangle's position.
     * @param width Width of the rectangle.
     * @param height Height of the rectangle.
     * @param rectangleColor Color of the rectangle.
     */
    Rectangle(NVGcontext *vg, float posX, float posY, float width, float height, NVGcolor rectangleColor);

    /**
     * @brief Destructor for the Rectangle class.
     */
    ~Rectangle();

    /**
     * @brief Draws the rectangle on the screen.
     */
    void drawRectangle();

    /**
     * @brief Updates the rectangle's properties.
     */
    void updateRectangle();

    /**
     * @brief Gets the X-coordinate of the rectangle's position.
     * @return The X-coordinate as a float.
     */
    float getPosX() const;

    /**
     * @brief Gets the Y-coordinate of the rectangle's position.
     * @return The Y-coordinate as a float.
     */
    float getPosY() const;

    /**
     * @brief Gets the width of the rectangle.
     * @return The width as a float.
     */
    float getWidth() const;

    /**
     * @brief Gets the height of the rectangle.
     * @return The height as a float.
     */
    float getHeight() const;

    /**
     * @brief Gets the color of the rectangle.
     * @return The color as an NVGcolor object.
     */
    NVGcolor getRectangleColor() const;

    /**
     * @brief Sets the X-coordinate of the rectangle's position.
     * @param newPosX The new X-coordinate.
     */
    void setPosX(float newPosX);

    /**
     * @brief Sets the Y-coordinate of the rectangle's position.
     * @param newPosY The new Y-coordinate.
     */
    void setPosY(float newPosY);

    /**
     * @brief Sets the width of the rectangle.
     * @param newWidth The new width.
     */
    void setWidth(float newWidth);

    /**
     * @brief Sets the height of the rectangle.
     * @param newHeight The new height.
     */
    void setHeight(float newHeight);

    /**
     * @brief Sets the color of the rectangle.
     * @param newColor The new color as an NVGcolor object.
     */
    void setRectangleColor(NVGcolor newColor);

private:
    NVGcontext *vg;
    float posX;
    float posY;
    float width;
    float height;
    NVGcolor rectangleColor;
};

} // namespace elm::ui
#endif // ELM_RECTANGLE_HPP