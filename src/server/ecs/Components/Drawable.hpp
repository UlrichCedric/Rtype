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
    Drawable(): _offsetX(0), _offsetY(0), _sizeX(50), _sizeY(50), _path("EMPTY") {  }

    Drawable(std::string path, std::pair<int, int> offset, std::pair<int, int> size) {
        _sizeX = size.first;
        _sizeY = size.second;
        _offsetX = offset.first;
        _offsetY = offset.second;
        _path = path;
    }

    std::string getName(void) { return "drawable"; }
    int getEnum(void) { return DRAWABLE; };
    std::pair<int, int> getOffset(void) { return { _offsetX, _offsetY }; }
    std::pair<int, int> getSize(void) { return { _sizeX, _sizeY }; }
    std::string getPath(void) { return _path; }

    void setSize(std::pair<int, int> size) {
        _sizeX = size.first;
        _sizeY = size.second;
    }

    void setOffset(std::pair<int, int> offset) {
        _offsetX = offset.first;
        _offsetY = offset.second;
    }

    void setSprite(std::string path = "EMPTY") { _path = path; }

    ~Drawable() {  };

    private:
    int _offsetX;
    int _offsetY;
    int _sizeX;
    int _sizeY;
    int maxSizeX;
    int maxSizeY;
    std::string _path;
};
