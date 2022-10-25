#pragma once

#include <iostream>

class ISystem {
    public:
    virtual void run(void) = 0;
    virtual ~ISystem() = default;
};