#pragma once

#include <iostream>

class ISystem {
    public:
    virtual void run(std::vector<std::shared_ptr<Entity>> &, std::string) = 0;
    virtual ~ISystem(void) = default;
};