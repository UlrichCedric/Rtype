#pragma once

#include "../IComponent.hpp"

/**
 *@brief Does the sprite have to repeat ? (prallax)
 */
class Repeatable: public IComponent {
    public:

    Repeatable(bool isRepeatable = true): _isRepeatable(isRepeatable) {  }
    Repeatable(Repeatable &r): _isRepeatable(r._isRepeatable) {  }

    std::string getName(void) override { return "repeatable"; }
    components getEnum(void) override { return REPEATABLE; };
    void setIfRepeating(bool isRepeatable) { _isRepeatable = isRepeatable; }
    bool getIfRepeating() { return _isRepeatable; }

    ~Repeatable() override = default;

    private:
    bool _isRepeatable;
};