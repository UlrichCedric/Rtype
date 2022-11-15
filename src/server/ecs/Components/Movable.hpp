#pragma once

#include "../AComponent.hpp"
#include <utility>
#include <iostream>

/**
 * @brief This is a Movable point component
 * @id : movable
 */
class Movable: public AComponent {
    public:
    Movable(bool movable = true): _movable(movable) {}
    Movable(Movable &m) { _movable = m._movable; }

    std::string getName(void) override { return "movable"; }
    components getEnum(void) override { return MOVABLE; }
    void setMovable(bool movable) { _movable = movable; }

    ~Movable() = default;

    private:
    bool _movable;
};