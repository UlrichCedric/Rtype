#pragma once

#include "../AComponent.hpp"
#include "../constants.hpp"

/**
 *@brief Does the sprite have to repeat ? (prallax)
 */
class Repeatable: public AComponent {

    public:

    Repeatable(bool isRepeatable = true): _isRepeatable(isRepeatable) {  }
    Repeatable(Repeatable &r): _isRepeatable(r._isRepeatable) {  }

    std::string getName(void) { return "repeatable"; }
    components getEnum(void) { return REPEATABLE; };
    void setIfRepeating(bool isRepeatable) { _isRepeatable = isRepeatable; }
    bool getIfRepeating() { return _isRepeatable; }

    ~Repeatable() {  }

    private:

    bool _isRepeatable;
};
