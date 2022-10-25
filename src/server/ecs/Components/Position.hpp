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
    Position(std::pair<int, int> pos): _x(pos.first), _y(pos.second) {  };
    Position(int x = 0, int y = 0): _x(x), _y(y) {  };
    std::string getName(void) { return "position"; }
    int getEnum(void) { return POSITION; };
    void setXPos(int x) { _x = x; };
    void setYPos(int y) { _y = y; };
    void setPos(int x, int y) {
        _x = x;
        _y = y;
    };

    void setPos(std::pair<int, int> pos) {
        _x = pos.first;
        _y = pos.second;
    };

    std::pair<int, int> getPos(void) { return std::make_pair(_x, _y); }
    int getXPos(void) { return _x; };
    int getYPos(void) { return _y; };
    ~Position() {  };

    private:
    int _x;
    int _y;
};

bool operator==(Position& p1, Position& p2) {
    return p1.getXPos() == p2.getXPos() && p1.getYPos() == p2.getYPos();
}
bool operator!=(Position& p1, Position& p2) {
    return p1.getXPos() != p2.getXPos() || p1.getYPos() != p2.getYPos();
}
