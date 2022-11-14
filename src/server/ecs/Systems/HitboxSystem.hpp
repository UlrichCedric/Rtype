#pragma once

#include "../ASystem.hpp"
#include "../Components/Hitbox.hpp"
#include "../Components/Position.hpp"

#include <memory>

class HitboxSystem: public ASystem {
    public:

    HitboxSystem(void) = default;

    bool isPlayerHit(
        std::pair<float, float> playerPos,
        std::pair<float, float> playerSize,
        std::vector<std::shared_ptr<Entity>> &list
    ) {
        if (list.empty()) {
            return false;
        }
        Hitbox h = Hitbox(playerSize, playerPos);

        for (auto e: list) {
            if (!e->has(HITBOX)) {
                continue;
            }
            auto h2 = std::dynamic_pointer_cast<Hitbox>(e->getComponent(HITBOX));
            if (h.isCollidingWith(h2)) {
                return true;
            }
        }
        return false;
    }

    void run(std::vector<std::shared_ptr<Entity>> &list, std::string) override {
        if (list.empty()) {
            return;
        }

        for (auto &e : list) {
            if (!e->has(HITBOX) || !e->has(POSITION) || !e->has(DRAWABLE)) {
                continue;
            }
            auto hb = std::dynamic_pointer_cast<Hitbox>(e->getComponent(HITBOX));
            auto hp = std::dynamic_pointer_cast<Position>(e->getComponent(POSITION));
            auto hd = std::dynamic_pointer_cast<Drawable>(e->getComponent(DRAWABLE));
            hb->setPos(hp->getPos());
            hb->setSize(hd->getSize());

            try {
                for (auto &el: list) {
                    if (!el->has(HITBOX) || e->getId() == el->getId()) {
                        continue;
                    }
                    auto el_hb = std::dynamic_pointer_cast<Hitbox>(el->getComponent(HITBOX));
                    if (*(el.get()) == *(e.get())) {
                        auto p = std::dynamic_pointer_cast<Position>(el->getComponent(POSITION));
                        auto v = std::dynamic_pointer_cast<Velocity>(el->getComponent(VELOCITY));
                        v->setYVelocity(v->getYVelocity() != 0.0 ? -1.0 * v->getYVelocity() : -1.0);
                    }
                }
            } catch (Error &e) {
                std::cerr << "HitboxSystem error: " << e.what() << std::endl;
            }
        }
    }

    ~HitboxSystem(void) override = default;

    private:
    bool isBetween(float a, float b, float c) { return (a < b && b < c); }
    bool areColliding(std::shared_ptr<Hitbox> h1, std::shared_ptr<Hitbox> h2) {
        return h1->isCollidingWith(h2);
    }
};