#pragma once

#include "../ASystem.hpp"
#include "../Components/Position.hpp"
#include "../Components/Velocity.hpp"

class Draw: public ASystem {
    public:
    Draw(std::list<std::shared_ptr<Entity>> &list): ASystem(list) {  };

    void run(void) override {
        for (auto element: _entities) {
            auto e = element.get();

            if (e->has("draw") && e->has("position") && e->has("velocity")) {
                auto pos = e->getComponent("position").get()->getPosition();
                auto vel = e->getComponent("velocity").get()->getVelocity();
                pos.first += vel.first;
                pos.second += vel.second;
                e->getComponent("position").get()->setPosition(pos);
            }
        }
    }

    ~Draw() {  }
};