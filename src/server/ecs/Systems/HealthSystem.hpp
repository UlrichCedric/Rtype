#pragma once

#include "../ASystem.hpp"
#include "../Components/Health.hpp"

class HealthSystem: public ASystem {
    public:
    HealthSystem(void) {  };

    void run(std::list<std::shared_ptr<Entity>> &list) override {
        for (auto element : list) {
            if (element.get()->has("health")) {
                Health *hp = static_cast<Health *>(element.get()->getComponent("health").get());
                if (hp->getHp() <= 0) {
                    element.get()->removeComponent(DRAWABLE);
                    return;
                }
            }
        }
    }

    ~HealthSystem() {  }
};