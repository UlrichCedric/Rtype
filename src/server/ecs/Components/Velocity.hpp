#pragma once

#include "../AComponent.hpp"
#include "../constants.hpp"

class Velocity: public AComponent {
    public:

    Velocity(float x = 0, float y = 0): _x(x), _y(y) {  }
    Velocity(Velocity &v): _x(v._x), _y(v._y) {  }

    std::string getName(void) override { return "velocity"; }
    components getEnum(void) override { return VELOCITY; };
    void setVelocity(float x, float y) { _x = x; _y = y; }
    void setXVelocity(float x) { _x = x; }
    void setYVelocity(float y) { _y = y; }
    float getXVelocity(void) const { return _x; }
    float getYVelocity(void) const { return _y; }
    std::pair<float, float> getVelocity(void) const { return { _x, _y }; }

    ~Velocity() override = default;

    private:
    float _x;
    float _y;
};

inline bool operator==(const Velocity& v1, const Velocity& v2) {
    return v1.getXVelocity() == v2.getXVelocity() && v1.getYVelocity() == v2.getYVelocity();
}
inline bool operator!=(const Velocity& v1, const Velocity& v2) {
    return v1.getXVelocity() != v2.getXVelocity() || v1.getYVelocity() != v2.getYVelocity();
}