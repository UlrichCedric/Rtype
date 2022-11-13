#include "../ASystem.hpp"
#include "../Components/Hitbox.hpp"
#include "../Components/Position.hpp"

#include <memory>

class HitboxSystem: public ASystem {
    public:

    HitboxSystem(void) = default;

    //TODO Apparently, this shit doesn't work
    void run(std::vector<std::shared_ptr<Entity>> &list) override {
        if (list.empty()) {
            return;
        }

        for (auto &e : list) {
            if (!e->has(HITBOX)) {
                continue;
            }
            auto hb = std::dynamic_pointer_cast<Hitbox>(e->getComponent(HITBOX));

            try {
                for (auto &el: list) {
                    if (!el->has(HITBOX) || e->getId() == el->getId()) {
                        continue;
                    }
                    auto el_hb = std::dynamic_pointer_cast<Hitbox>(el->getComponent(HITBOX));
                    if (areColliding(hb, el_hb)) {
                        auto p = std::dynamic_pointer_cast<Position>(el->getComponent(POSITION));
                        auto v = std::dynamic_pointer_cast<Velocity>(el->getComponent(VELOCITY));
                        if (v->getYVelocity() != 0) {
                            v->setYVelocity(-1 * v->getYVelocity());
                        } else if (v->getXVelocity() != 0) {
                            v->setXVelocity(-1 * v->getXVelocity());
                        } else {
                            p->setYPos(p->getYPos() + 40);
                        }
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
        //TODO do not forget to fill this function
        return true;
    }
};