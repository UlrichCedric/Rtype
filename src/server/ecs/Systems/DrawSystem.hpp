#pragma once

#include "../ASystem.hpp"
#include "../Components/Position.hpp"
#include "../Components/Velocity.hpp"
#include "../constants.hpp"

#include <vector>
#include <memory>
#include <ctime>

class DrawSystem: public ASystem {
    public:
    DrawSystem(void) = default;

    void run(std::vector<std::shared_ptr<Entity>> &list) override {
        if (list.empty()) {
            return;
        }

        for (auto element: list) {
            std::srand(std::time(nullptr));
            // std::cout << "running DrawSystem for element with id " << element->getId() << std::endl;
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

                // update position
                if (betw(-50.0, p.first + v.first, 1115.0) ||
                    betw(-50.0, p.second + v.second, 870.0)
                ) {
                    pos->setXPos(p.first + v.first);
                    pos->setYPos(p.second + v.second);
                }

                // restart if it goes out of the map
                if (pos->getXPos() < -100.0) {
                    pos->setXPos(1300.0);
                }
                if (pos->getYPos() < -50.0 || pos->getYPos() > 750) {
                    pos->setYPos(static_cast<float>(std::rand() % 700));
                    pos->setXPos(1300.0);
                }
                vel->setXVelocity(v.first * xVelocityMultiplier);
            } catch (Error &err) {
                std::cerr << "Error: " << err.what() << std::endl;
            }
        }
        xVelocityMultiplier = xVelocityMultiplier > 1.00055 ? 1.0 : xVelocityMultiplier + 0.0000001;
    }

    ~DrawSystem(void) override = default;

    private:
    float xVelocityMultiplier = 1.0;
};