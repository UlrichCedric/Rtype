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

        for (auto element: list) {
            auto e = element.get();
            if (e == nullptr) {
                continue;
            }

            if (!e->has("draw") || !e->has("position") || !e->has("velocity")) {
                continue;
            }

            try {
                auto pos = std::dynamic_pointer_cast<Position>(e->getComponent(POSITION));
                std::pair<float, float> p = pos->getPos();
                auto vel = std::dynamic_pointer_cast<Velocity>(e->getComponent(VELOCITY));
                std::pair<int, int> v = vel->getVelocity();

                if (betw(-15, p.first + v.first, 1115) || betw(-15, p.second + v.second, 870)) {
                    p.first += v.first;
                    p.second += v.second;
                    pos->setPos(p);
                }
            } catch (Error &err) {
                std::cerr << "Error: " << err.what() << std::endl;
            }
        }
    }

    ~DrawSystem(void) override = default;
};