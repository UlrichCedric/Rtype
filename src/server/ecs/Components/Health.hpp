#pragma once

#include "../AComponent.hpp"
#include "../constants.hpp"

#include <utility>
#include <iostream>

/**
 * @brief This is a Health point component
 * @id : health
 */
class Health: public AComponent {

    public:
    Health(int hp = 100): _hp(hp) {  }
    Health(Health &h): _hp(h._hp) {  }
    std::string getName(void) override { return "health"; }
    components getEnum(void) override { return HEALTH; };
    void setHp(int hp) { _hp = hp; }
    int getHp(void) { return _hp; }
    void takeDamage(int damage = 0) { _hp -= damage; }

    ~Health() override = default;

    private:
    int _hp;
};