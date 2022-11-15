#pragma once

#include <iostream>
#include "constants.hpp"

class IComponent {
    public:
    virtual ~IComponent() = default;
    virtual std::string getName(void) = 0;
    virtual components getEnum(void) = 0;
};
