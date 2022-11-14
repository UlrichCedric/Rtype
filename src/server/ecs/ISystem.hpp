#pragma once

#include <iostream>
#include <vector>
#include <memory>

class ISystem {
    public:
    virtual void run(std::vector<std::shared_ptr<Entity>> &, std::string) = 0;
    virtual ~ISystem(void) = default;
};