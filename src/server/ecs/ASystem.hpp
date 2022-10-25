#pragma once

#include "ISystem.hpp"
#include "Entity.hpp"
#include <list>
#include <memory>

class ASystem : public ISystem {
    public:
    ASystem(std::list<std::shared_ptr<Entity>> &list): _entities(list) {  };
    void run(void) = 0;
    ~ASystem() = default;

    protected:
    std::list<std::shared_ptr<Entity>> &_entities;
};