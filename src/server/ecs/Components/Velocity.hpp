#pragma once

#include "../AComponent.hpp"
#include "../constants.hpp"

class Velocity: public AComponent {

    public:

    Velocity(int x = 0, int y = 0): _x(x), _y(y) {  }
    Velocity(Velocity &v): _x(v._x), _y(v._y) {  }

    std::string getName(void) { return "velocity"; }
    components getEnum(void) { return VELOCITY; };
    void setVelocity(int x, int y) { _x = x; _y = y; }
    void setXVelocity(int x) { _x = x; }
    void setYVelocity(int y) { _y = y; }
    int getXVelocity(void) const { return _x; }
    int getYVelocity(void) const { return _y; }
    std::pair<int, int> getVelocity(void) const { return std::pair<int, int>(_x, _y); }

    ~Velocity() {  }

    private:

    int _x;
    int _y;
};

inline bool operator==(const Velocity& v1, const Velocity& v2) {
    return v1.getXVelocity() == v2.getXVelocity() && v1.getYVelocity() == v2.getYVelocity();
}
inline bool operator!=(const Velocity& v1, const Velocity& v2) {
    return v1.getXVelocity() != v2.getXVelocity() || v1.getYVelocity() != v2.getYVelocity();
}