/**
 * Daydream library
 * @file elm_Image.hpp
 * @author daviMassini
 * @copyright NanoVG for Deko3D (Adubbz) - daviMassini
 */

#ifndef ELM_IMAGE_HPP
#define ELM_IMAGE_HPP

#include "nanovg.h"

/**
 * @class Image
 * @brief Represents an image element in the UI that can be drawn and updated.
 *
 * The `Image` class provides functionality to create, manipulate, and render images
 * within a NanoVG context. It supports properties such as position, size, rotation angle,
 * image path, and transparency.
 */
namespace elm::ui {

class Image {
public:
    /**
     * @brief Creates a new Image instance.
     *
     * @param vg Pointer to the NanoVG context.
     * @param posX X-coordinate of the image's position.
     * @param posY Y-coordinate of the image's position.
     * @param width Width of the image.
     * @param height Height of the image.
     * @param imagePath Path to the image file.
     * @param angle Rotation angle of the image in radians (default is 0.0f).
     * @param alpha Transparency level of the image (default is 1.0f, fully opaque).
     * @return A new `Image` instance.
     */
    static Image New(NVGcontext *vg, float posX, float posY,
                     float width, float height, const char *imagePath,
                     float angle = 0.0f, float alpha = 1.0f);

    /**
     * @brief Constructs an Image object.
     *
     * @param vg Pointer to the NanoVG context.
     * @param posX X-coordinate of the image's position.
     * @param posY Y-coordinate of the image's position.
     * @param width Width of the image.
     * @param height Height of the image.
     * @param imagePath Path to the image file.
     * @param angle Rotation angle of the image in radians.
     * @param alpha Transparency level of the image.
     */
    Image(NVGcontext *vg, float posX, float posY,
          float width, float height, const char *imagePath,
          float angle = 0.0f, float alpha = 1.0f);

    /**
     * @brief Destructor for the Image object.
     */
    ~Image();

    /**
     * @brief Draws the image on the NanoVG context.
     */
    void drawImage();

    /**
     * @brief Updates the image properties or state.
     */
    void update();

    /**
     * @brief Gets the X-coordinate of the image's position.
     * @return The X-coordinate of the image's position.
     */
    float getPosX() const;

    /**
     * @brief Gets the Y-coordinate of the image's position.
     * @return The Y-coordinate of the image's position.
     */
    float getPosY() const;

    /**
     * @brief Gets the width of the image.
     * @return The width of the image.
     */
    float getWidth() const;

    /**
     * @brief Gets the height of the image.
     * @return The height of the image.
     */
    float getHeight() const;

    /**
     * @brief Gets the rotation angle of the image.
     * @return The rotation angle of the image in radians.
     */
    float getAngle() const;

    /**
     * @brief Gets the file path of the image.
     * @return The file path of the image.
     */
    const char *getImagePath() const;

    /**
     * @brief Gets the transparency level of the image.
     * @return The transparency level of the image.
     */
    float getAlpha() const;

    /**
     * @brief Sets the X-coordinate of the image's position.
     * @param newPosX The new X-coordinate.
     */
    void setPosX(float newPosX);

    /**
     * @brief Sets the Y-coordinate of the image's position.
     * @param newPosY The new Y-coordinate.
     */
    void setPosY(float newPosY);

    /**
     * @brief Sets the width of the image.
     * @param newWidth The new width.
     */
    void setWidth(float newWidth);

    /**
     * @brief Sets the height of the image.
     * @param newHeight The new height.
     */
    void setHeight(float newHeight);

    /**
     * @brief Sets the rotation angle of the image.
     * @param newAngle The new rotation angle in radians.
     */
    void setAngle(float newAngle);

    /**
     * @brief Sets the file path of the image.
     * @param newImagePath The new file path.
     */
    void setImagePath(const char *newImagePath);

    /**
     * @brief Sets the transparency level of the image.
     * @param newAlpha The new transparency level.
     */
    void setAlpha(float newAlpha);

private:
    NVGcontext *vg;
    float posX;
    float posY;
    float width;
    float height;
    const char *imagePath;
    float angle;
    float alpha;

    int loadImage;
};

} // namespace elm::ui
#endif // ELM_IMAGE_HPP