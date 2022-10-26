#pragma once

#include <iostream>
#include "IComponent.hpp"
#include <list>
#include <memory>

#include "IComponent.hpp"
#include "constants.hpp"
#include "Entity.hpp"
#include "../../Errors.hpp"

#include "Components/Drawable.hpp"
#include "Components/Health.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "Components/Repeatable.hpp"
#include "Components/Movable.hpp"
#include "Components/Sound.hpp"
#include "Components/Scale.hpp"
#include "Components/Uuid.hpp"

class Entity {

    public:

    Entity(size_t id = 0) {
        std::cout << "Entity constructor with id " << id << std::endl;
        _id = id;
    }

    Entity(Entity &e) {
        _id = e.getId();
        _comps.clear();
        for (auto comp: e._comps) {
            _comps.push_back(comp);
        }
        std::cout << "Entity constructor by copy with id " << _id << std::endl;
    }

    size_t getId(void) { return _id; }
    void setId(std::size_t id) { _id = id; }

    bool has(std::string name) {
        for (auto c: _comps) {
            if (c->getName() == name) {
                return true;
            }
        }
        return false;
    }

    bool has(int co) {
        for (auto c: _comps) {
            std::cout << co << std::endl;
            if (c->getEnum() == co) {
                return true;
            }
        }
        return false;
    }

    void addComponent(int cmp) {
        for (auto c: intToCmps) {
            if (c.first == cmp) {
                std::shared_ptr<IComponent> p = c.second();
                if (p.get() == nullptr) {
                    throw Error("Empty component list in addComponent");
                }
                _comps.push_back(p);
                return;
            }
        }
        throw Error("Component not found in addComponent");
    }

    void addComponent(std::string name) {
        for (auto c: strToCmps) {
            if (c.first == name) {
                std::shared_ptr<IComponent> p = c.second();
                if (p.get() == nullptr) {
                    throw Error("Empty component list in addComponent");
                }
                _comps.push_back(std::move(p));
                return;
            }
        }
        throw Error("Component not found in addComponent");
    }

    void removeComponent(int cmp) {
        if (!has(cmp)) {
            std::cerr << "Error: couldn't find component number " << cmp << std::endl;
            return;
        }

        for (auto el: _comps) {
            if (el.get()->getEnum() == cmp) {
                _comps.remove(el);
                return;
            }
        }
    }

    void removeComponent(std::string name) {
        if (!has(name)) {
            std::cerr << "Error: couldn't find component " << name << std::endl;
            return;
        }

        for (auto el: _comps) {
            if (el.get()->getName() == name) {
                _comps.remove(el);
                return;
            }
        }
    }

    std::shared_ptr<IComponent> getComponent(std::string name) {
        for (auto comp: _comps) {
            auto c = comp.get();

            if (c->getName() == name) {
                return comp;
            }
        }
        throw Error("Couldn't find component");
    }

    std::shared_ptr<IComponent> getComponent(components c) {
        for (auto comp: _comps) {
            auto co = comp.get();

            if (co->getEnum() == c) {
                return comp;
            }
        }
        throw Error("Couldn't find component");
    }

    ~Entity() {  }

    std::list<std::shared_ptr<IComponent>> _comps;

    private:
    size_t _id;

    const std::unordered_map<std::string, std::function<std::shared_ptr<IComponent>(void)>> strToCmps = {
        { "drawable", [&](void) { return std::make_shared<Drawable>(); } },
        { "health", [&](void) { return std::make_shared<Health>(); } },
        { "velocity", [&](void) { return std::make_shared<Velocity>(); } },
        { "position", [&](void) { return std::make_shared<Position>(); } },
        { "repeatable", [&](void) { return std::make_shared<Repeatable>(); } },
        { "movable", [&](void) { return std::make_shared<Movable>(); } },
        { "sound", [&](void){ return std::make_shared<Sound>(); } },
        { "uuid", [&](void){ return std::make_shared<Uuid>(); } },
        { "scale", [&](void){ return std::make_shared<Scale>(); } }
    };

    const std::unordered_map<components, std::function<std::shared_ptr<IComponent>(void)>> intToCmps = {
        { DRAWABLE, [&](void) { return std::make_shared<Drawable>(); } },
        { HEALTH, [&](void) { return std::make_shared<Health>(); } },
        { VELOCITY, [&](void) { return std::make_shared<Velocity>(); } },
        { POSITION, [&](void) { return std::make_shared<Position>(); } },
        { REPEATABLE, [&](void) { return std::make_shared<Repeatable>(); } },
        { MOVABLE, [&](void) { return std::make_shared<Movable>(); } },
        { SOUND, [&](void) { return std::make_shared<Sound>(); } },
        { SCALE, [&](void) { return std::make_shared<Scale>(); } },
        { UUID, [&](void) { return std::make_shared<Uuid>(); } }
    };
};

inline bool operator==(Entity &ent1, Entity &ent2) { return ent1.getId() == ent2.getId(); }
inline bool operator!=(Entity &ent1, Entity &ent2) { return ent1.getId() != ent2.getId(); }
inline bool operator< (Entity &ent1, Entity &ent2) { return ent1.getId() < ent2.getId();  }
inline bool operator> (Entity &ent1, Entity &ent2) { return ent1.getId() > ent2.getId();  }
inline bool operator<=(Entity &ent1, Entity &ent2) { return ent1.getId() <= ent2.getId(); }
inline bool operator>=(Entity &ent1, Entity &ent2) { return ent1.getId() >= ent2.getId(); }
