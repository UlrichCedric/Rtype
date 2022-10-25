#pragma once

#include "../ASystem.hpp"
#include "../Components/Health.hpp"

class HealthSystem: public ASystem {
    public:
    HealthSystem(std::list<std::shared_ptr<Entity>> &list): ASystem(list) {  };

    void run(void) override {
        for (auto element : _entities) {
            if (element.get()->has("health")) {
                Health *hp = element.get()->getComponent("health").get();
                if (hp->getHp() <= 0) {
                    element.get()->removeComponent(DRAWABLE);
                    return;
                }
            }
        }
    }

    ~HealthSystem() {  }
};