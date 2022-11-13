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
            std::cout << "running DrawSystem for element with id " << element->getId() << std::endl;
            auto e = element.get();
            if (e == nullptr) {
                continue;
            }

            if (!e->has(DRAWABLE) || !e->has(POSITION) || !e->has(VELOCITY)) {
                continue;
            }

            try {
                auto pos = std::dynamic_pointer_cast<Position>(e->getComponent(POSITION));
                std::pair<float, float> p = pos->getPos();
                auto vel = std::dynamic_pointer_cast<Velocity>(e->getComponent(VELOCITY));
                std::pair<float, float> v = vel->getVelocity();

                std::cout << "old / new : " << p.first;

                if (betw(-15.0, p.first + v.first, 1115.0) ||
                    betw(-15.0, p.second + v.second, 870.0)
                ) {
                    pos->setXPos(p.first + v.first);
                    pos->setYPos(p.second + v.second);
                }
                std::cout << " / " << pos->getXPos() << std::endl;
            } catch (Error &err) {
                std::cerr << "Error: " << err.what() << std::endl;
            }
        }
    }

    ~DrawSystem(void) override = default;
};