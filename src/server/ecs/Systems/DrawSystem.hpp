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

    void run(std::vector<std::shared_ptr<Entity>> &list) {
        std::cout << "run draw system" << std::endl;
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

                if (betw(-15, p.first + v.first, 1115) || betw(-15, p.second + v.second, 870)) {
                    pos->setPos(p.first + static_cast<float>(v.first), p.second + static_cast<float>(v.second));
                    std::cout << "drawsystem run: " << pos->getPos().first << " :: " << pos->getPos().second << std::endl;
                }
            } catch (std::exception & e) {
                std::cout << "y'a une couille wolah" << std::endl;
            }
        }
    }

    ~DrawSystem() override = default;
};