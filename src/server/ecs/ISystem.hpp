#pragma once

#include <iostream>

class ISystem {
    public:
    virtual void run(std::vector<std::shared_ptr<Entity>> &) = 0;
    virtual ~ISystem(void) = default;
};