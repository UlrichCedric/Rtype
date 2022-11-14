#pragma once

#include "../ASystem.hpp"
#include "../Components/Health.hpp"

#include <memory>

class HealthSystem: public ASystem {
    public:
    HealthSystem(void) = default;

    void run(std::vector<std::shared_ptr<Entity>> &list, std::string) override {
        for (auto element : list) {
            if (element.get()->has(HEALTH)) {
                auto hp = std::dynamic_pointer_cast<Health>(element.get()->getComponent(HEALTH));
                if (hp->getHp() <= 0) {
                    element.get()->removeComponent(DRAWABLE);
                    return;
                }
            }
        }
    }

    ~HealthSystem() override = default;
};