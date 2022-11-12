#pragma once

#include "../AComponent.hpp"
#include <utility>
#include <iostream>

/**
 * @brief This is a Movable point component
 * @param movable
 */
class Movable: public AComponent {
    public:
    Movable(bool movable = true): _movable(movable) {  }
    Movable(Movable &m) { _movable = m._movable; }
    std::string getName(void) { return "movable"; }
    components getEnum(void) { return MOVABLE; }
    void setMovable(bool movable) { _movable = movable; }
    ~Movable() = default;

    private:
    bool _movable;
};