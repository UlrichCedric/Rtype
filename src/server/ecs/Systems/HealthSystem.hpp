#pragma once

#include "../ASystem.hpp"
#include "../Components/Health.hpp"

#include <memory>
#include <vector>

class HealthSystem: public ASystem {
    public:
    HealthSystem(void) = default;

    void run(std::vector<std::shared_ptr<Entity>> &list, std::string) override {
        for (auto element : list) {
            if (element->has(HEALTH)) {
                auto hp = std::dynamic_pointer_cast<Health>(element->getComponent(HEALTH));
                if (hp->getHp() <= 0) {
                    element->removeComponent(DRAWABLE);
                    auto it = std::remove(list.begin(), list.end(), element);
                    list.erase(it, list.end());
                    return;
                }
            }
        }
    }

    ~HealthSystem() override = default;
};