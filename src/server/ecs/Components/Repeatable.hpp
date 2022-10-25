#pragma once

#include "../IComponent.hpp"

/**
 *@brief Does the sprite have to repeat ? (prallax)
 */
class Repeatable: public IComponent {
    public:

    Repeatable(bool isRepeatable = true): _isRepeatable(isRepeatable) {  }
    std::string getName(void) { return "repeatable"; }
    int getEnum(void) { return REPEATABLE; };
    void setIfRepeating(bool isRepeatable) { _isRepeatable = isRepeatable; }
    bool getIfRepeating() { return _isRepeatable; }
    ~Repeatable() {  }

    private:

    bool _isRepeatable;
};