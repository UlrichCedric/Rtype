#pragma once

#include "../AComponent.hpp"
#include "../constants.hpp"

#include <utility>
#include <iostream>


class Drawable: public AComponent {
    public:

    /**
     * @brief Construct a new Drawable object
     *
     */
    Drawable():
        _offsetX(0.0),
        _offsetY(0.0),
        _sizeX(50.0),
        _sizeY(50.0),
        _path("EMPTY")
    {  }

    /**
     * @brief Construct a new Drawable object
     *
     * @param path texture path
     * @param offset rectangle offset
     * @param size sprite size
     */
    Drawable(
        std::string path,
        std::pair<float, float> offset,
        std::pair<float, float> size
    ):
        _sizeX(size.first),
        _sizeY(size.second),
        _offsetX(offset.first),
        _offsetY(offset.second),
        _path(std::move(path))
    {  }

    /**
     * @brief Construct a new Drawable object from an existing one
     *
     * @param d existing Drawable object
     */
    Drawable(Drawable &d):
        _sizeX(d._sizeX),
        _sizeY(d._sizeY),
        _offsetX(d._offsetX),
        _offsetY(d._offsetY),
        _path(d._path)
    {  }

    /**
     * @brief Get the name of the component
     *
     * @return std::string returns the name of the component as a string
     */
    std::string getName(void) { return "drawable"; }

    /**
     * @brief Get the name of the component
     *
     * @return int returns the name of the component as an int
     */
    components getEnum(void) { return DRAWABLE; };

    /**
     * @brief Get the Offset object
     *
     * @return std::pair<float, float> returns the offset for the rectangle x and y
     */
    std::pair<float, float> getOffset(void) { return { _offsetX, _offsetY }; }

    /**
     * @brief Get the Size object
     *
     * @return std::pair<float, float> returns the size of the drawable x and y
     */
    std::pair<float, float> getSize(void) { return { _sizeX, _sizeY }; }

    /**
     * @brief Get the Max Offset object
     *
     * @return std::pair<float, float> returns the offset for the rectangle
     */
    std::pair<float, float> getMaxOffset(void) { return { _maxSizeX, _maxSizeY }; }

    /**
     * @brief Get the Path object
     *
     * @return std::string returns the current texture path
     */
    std::string getPath(void) { return _path; }

    /**
     * @brief Set the Size object
     *
     * @param size height and width for the size
     */
    void setSize(std::pair<float, float> size) {
        _sizeX = size.first;
        _sizeY = size.second;
    }

    /**
     * @brief Set the Offset object
     *
     * @param offset x and y of the offset
     */
    void setOffset(std::pair<float, float> offset) {
        _offsetX = offset.first;
        _offsetY = offset.second;
    }

    /**
     * @brief Set the size of the rectangle
     *
     * @param new rectangle size
     */
    void setRectSize(std::pair<float, float> rectSize) {
        _rectSizeX = rectSize.first;
        _rectSizeY = rectSize.second;
    }

    /**
     * @brief Get the size of the rectangle
     *
     * @return std::pair<float, float> rectangle Size
     */
    std::pair<float, float> getRectSize(void) {
        return { _rectSizeX, _rectSizeY };
    }

    /**
     * @brief Set the Sprite object
     *
     * @param texture path
     */
    void setSprite(std::string path = "EMPTY") { _path = path; }

    ~Drawable() override = default;

    private:
    float _offsetX;     // x rectangle offset
    float _offsetY;     // y rectangle offset
    float _sizeX;       // x size of the sprite
    float _sizeY;       // y size of the sprite
    float _rectSizeX;   // size of the rectangle X
    float _rectSizeY;   // size of the rectangle Y
    float _maxSizeX;    // x max offset for the rectangle
    float _maxSizeY;    // y max offset for the rectangle
    std::string _path;  // texture path
};
