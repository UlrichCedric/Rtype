#pragma once

#include "../AComponent.hpp"
#include <utility>

class Scale: public AComponent {

    public:

    Scale(float x = 1.0f, float y = 1.0f) {  }
    Scale(Scale &s): _x(s._x), _y(s._y) {  }

    std::string getName(void) override { return "scale"; }
    int getEnum(void) override { return SCALE; };

    float getXScale(void) { return _x; }
    float getYScale(void) { return _y; }
    std::pair<float, float> getScale(void) { return std::make_pair(_x, _y); }

    void setScale(float x, float y) {
        _x = x;
        _y = y;
    }

    void setScale(std::pair<float, float> scale) {
        _x = scale.first;
        _y = scale.second;
    }

    void setXScale(float x) { _x = x; }
    void setYScale(float y) { _y = y; }

    ~Scale(void) {  }

    private:

    float _x;
    float _y;
};