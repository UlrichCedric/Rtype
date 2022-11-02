#pragma once

#include "../AComponent.hpp"
#include "../constants.hpp"

#include <utility>
#include <iostream>

/**
 * @brief This is a drawable sprite
 * @id : drawable
 */
class Drawable: public AComponent {
    public:
    Drawable(): _offsetX(0.0), _offsetY(0.0), _sizeX(50.0), _sizeY(50.0), _path("EMPTY") {  }

    Drawable(std::string path, std::pair<float, float> offset, std::pair<float, float> size) {
        _sizeX = size.first;
        _sizeY = size.second;
        _offsetX = offset.first;
        _offsetY = offset.second;
        _path = path;
    }

    Drawable(Drawable &d) {
        _sizeX = d._sizeX;
        _sizeY = d._sizeY;
        _offsetX = d._offsetX;
        _offsetY = d._offsetY;
        _path = d._path;
    }

    std::string getName(void) { return "drawable"; }
    int getEnum(void) { return DRAWABLE; };
    std::pair<float, float> getOffset(void) { return { _offsetX, _offsetY }; }
    std::pair<float, float> getSize(void) { return { _sizeX, _sizeY }; }
    std::pair<float, float> getMaxOffset(void) { return { _maxSizeX, _maxSizeY }; }
    std::string getPath(void) { return _path; }

    void setSize(std::pair<float, float> size) {
        _sizeX = size.first;
        _sizeY = size.second;
    }

    void setOffset(std::pair<float, float> offset) {
        _offsetX = offset.first;
        _offsetY = offset.second;
    }

    void setSprite(std::string path = "EMPTY") { _path = path; }

    ~Drawable() {  };

    private:
    float _offsetX;
    float _offsetY;
    float _sizeX;
    float _sizeY;
    float _maxSizeX;
    float _maxSizeY;
    std::string _path;
};
