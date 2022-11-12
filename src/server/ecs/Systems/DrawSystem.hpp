#pragma once

#include "../ASystem.hpp"
#include "../Components/Position.hpp"
#include "../Components/Velocity.hpp"
#include "../constants.hpp"

#include <vector>
#include <memory>

class DrawSystem: public ASystem {
    public:
    DrawSystem(void) = default;

    void run(std::vector<std::shared_ptr<Entity>> &list) override {
        if (list.empty()) {
            return;
        }

        for (auto e: list) {
            if (!e->has(DRAWABLE) || !e->has(POSITION) || !e->has(VELOCITY)) {
                continue;
            }

            try {
                auto pos = std::dynamic_pointer_cast<Position>(e->getComponent(POSITION));
                std::pair<float, float> p = pos->getPos();
                auto vel = std::dynamic_pointer_cast<Velocity>(e->getComponent(VELOCITY));
                std::pair<int, int> v = vel->getVelocity();

                float x = p.first + static_cast<float>(v.first);
                float y = p.second + static_cast<float>(v.second);

                if (betw(-15.0, x, 1115.0) || betw(-15.0, y, 870.0)) {
                    pos->setPos(p.first + static_cast<float>(v.first), p.second + static_cast<float>(v.second));
                }

            } catch (Error &e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }

    ~DrawSystem() override = default;
};