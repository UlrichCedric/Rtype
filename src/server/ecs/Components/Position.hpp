#pragma once

#include "../AComponent.hpp"
#include "../constants.hpp"

#include <iostream>
#include <utility>

/**
 * @brief This is a position vector
 * @id : position
 */
class Position: public AComponent {
    public:
    Position(std::pair<float, float> pos): _x(pos.first), _y(pos.second) {  };
    Position(float x = 0, float y = 0): _x(x), _y(y) {  };
    Position(Position &p): _x(p._x), _y(p._y) {  };

    std::string getName(void) { return "position"; }
    components getEnum(void) { return POSITION; };
    void setXPos(float x) { _x = x; };
    void setYPos(float y) { _y = y; };
    void setPos(float x, float y) {
        _x = x;
        _y = y;
    };

    void setPos(std::pair<float, float> pos) {
        _x = pos.first;
        _y = pos.second;
    };

    std::pair<float, float> getPos(void) { return std::make_pair(_x, _y); }
    float getXPos(void) { return _x; };
    float getYPos(void) { return _y; };
    ~Position() {  };

    private:
    float _x;
    float _y;
};

inline bool operator==(Position& p1, Position& p2) {
    return p1.getXPos() == p2.getXPos() && p1.getYPos() == p2.getYPos();
}
inline bool operator!=(Position& p1, Position& p2) {
    return p1.getXPos() != p2.getXPos() || p1.getYPos() != p2.getYPos();
}
