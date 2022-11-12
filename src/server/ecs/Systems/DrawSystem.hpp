#pragma once

#include "../ASystem.hpp"
#include "../Components/Position.hpp"
#include "../Components/Velocity.hpp"
#include "../constants.hpp"

class DrawSystem: public ASystem {
    public:
    DrawSystem(void) {  }

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
                Position *pos = static_cast<Position *>(e->getComponent("position").get());
                std::pair<float, float> p = pos->getPos();
                Velocity *vel = static_cast<Velocity *>(e->getComponent("velocity").get());
                std::pair<int, int> v = vel->getVelocity();

                if (betw(-15, p.first + v.first, 1115) || betw(-15, p.second + v.second, 870)) {
                    p.first += v.first;
                    p.second += v.second;
                    pos->setPos(p);
                }
            } catch (std::exception & e) {
                std::cout << "y' a une couille wolah" << std::endl;
            }
        }
    }

    ~DrawSystem() {  }
};