#pragma once

#include "../ASystem.hpp"
#include "../Components/Position.hpp"
#include "../Components/Velocity.hpp"
#include "../constants.hpp"

#include <map>
#include <vector>
#include <memory>
#include <ctime>

class DrawSystem: public ASystem {
    public:
    DrawSystem(void) = default;

    void addLobby(std::string uuid) { xVelocityMultiplier[uuid] = 1.0; }

    void run(std::vector<std::shared_ptr<Entity>> &list, std::string uuid) override {
        if (list.empty()) {
            return;
        }

        if (xVelocityMultiplier[uuid] == 0.0) {
            std::cerr << "Error: wrong lobby uuid" << std::endl;
            return;
        }

        for (auto e: list) {
            std::srand(std::time(nullptr));
            // std::cout << "running DrawSystem for element with id " << element->getId() << std::endl;
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
                float mult = xVelocityMultiplier[uuid] < 0 ? 1.0F : xVelocityMultiplier[uuid];

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
                vel->setXVelocity(v.first * mult);

                // if id < 100 and got out of screen: bullet destroy
                if (e->getId() < 100 && pos->getXPos() > 1300.0) {
                    auto tmp = std::remove(list.begin(), list.end(), e);
                    list.erase(tmp, list.end());
                }
            } catch (Error &err) {
                std::cerr << "Error: " << err.what() << std::endl;
            }
        }

        if (xVelocityMultiplier[uuid] > 1.00055 || xVelocityMultiplier[uuid] < 0) {
            xVelocityMultiplier[uuid] = -1.0;
        } else {
            xVelocityMultiplier[uuid] += 0.0000001;
        }
    }

    ~DrawSystem(void) override = default;

    private:
    std::map<std::string, float> xVelocityMultiplier = {  };
};