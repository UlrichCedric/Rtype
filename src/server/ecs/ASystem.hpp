#pragma once

#include "ISystem.hpp"
#include "Entity.hpp"
#include <list>
#include <memory>

class ASystem : public ISystem {
    public:
    ASystem(void) {  };
    virtual void run(std::vector<std::shared_ptr<Entity>> &) = 0;
    ~ASystem(void) {  };
};