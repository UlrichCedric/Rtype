#pragma once

#include "../ASystem.hpp"
#include "../Components/Health.hpp"

#include <memory>
#include <vector>
#include <algorithm>

class HealthSystem: public ASystem {
    public:
    HealthSystem(void) = default;

    //TODO check if this shit work (I'm unsure about remove_if)
    void run(std::vector<std::shared_ptr<Entity>> &list) override {
        std::remove_if(list.begin(), list.end(), [](const std::shared_ptr<Entity> &e){
            if (!e->has(HEALTH)) {
                return false;
            }
            auto hp = std::dynamic_pointer_cast<Health>(e->getComponent(HEALTH));
            return hp->getHp() <= 0;
        });
    }

    ~HealthSystem(void) override = default;
};