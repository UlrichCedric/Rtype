#pragma once

#include "ISystem.hpp"
#include "Entity.hpp"
#include <vector>
#include <memory>

class ASystem : public ISystem {
    public:
    ASystem(void) = default;
    virtual void run(std::vector<std::shared_ptr<Entity>> &, std::string) = 0;
    ~ASystem(void) = default;
};