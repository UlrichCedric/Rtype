#pragma once

#include "Entity.hpp"
#include "ASystem.hpp"
#include "../../Errors.hpp"
#include "constants.hpp"

#include <list>
#include <memory>
#include <fstream>
#include <sstream>
#include <unordered_map>

/** Creates a new Factory
 *@brief Takes no arguments
 */
class Factory {
    public:

    Factory(): _last_id(0) {
        std::ifstream file("src/server/ecs/entities.conf");
        std::string string;
        std::string word;

        while (std::getline(file, string)) {
            if (string.empty()) {
                break;
            }
            std::string name = string.substr(0, string.find(':', 0));
            string = string.substr(string.find(':', 0) + 1, string.length() - 1);

            std::istringstream stream(string);
            Entity e;
            std::cout << "creating entity with id -1 : " << e.getId() << std::endl;

            while (stream >> word) {
                if (word.empty()) {
                    break;
                }
                for (auto _str: strToInt) {
                    if (word == _str.first) {
                        e.addComponent(_str.second);
                        break;
                    }
                }
            }

            _customs[name] = std::make_shared<Entity>(e);
        }

        for (auto entity: _customs) {
            for (int i = 0; i < comp_nb; ++i) {
                std::cout << "je get le component" << std::endl;
                try {
                    //TODO change this awful static cast
                    auto comp = entity.second.get()->getComponent(static_cast<components>(i)).get();
                    std::cout << i << " : ";
                    std::cout << comp->getName() << std::endl;
                } catch (Error &e) {
                    std::cerr << "tout cassé : " << e.what() << std::endl;
                }
            }
        }
    }

    std::shared_ptr<Entity> createEntity(std::string name) {
        for (auto custom: _customs) {
            if (custom.first == name) {
                std::cout << "Creating entity " << name << std::endl;
                std::shared_ptr<Entity> e = std::make_shared<Entity>(*custom.second.get());
                if (e == nullptr) {
                    std::cout << "Failed to create entity " << name << std::endl;
                }
                e.get()->setId(_last_id);
                return e;
            }
        }
        std::cerr << "Error entity creation: " << name << " not found" << std::endl;
        return nullptr;
    }

    std::shared_ptr<Entity> getEntityById(std::size_t id) {
        for (auto custom: _customs) {
            if (custom.second.get()->getId() == id) {
                std::shared_ptr<Entity> e = std::make_shared<Entity>(*custom.second.get());
                if (e == nullptr) {
                    std::cout << "Failed to get entity by id: " << id << std::endl;
                }
                return e;
            }
        }
        return nullptr;
    }

    ~Factory() {  }

    private:
    std::size_t _last_id;
    std::unordered_map<std::string, std::shared_ptr<Entity>> _customs;
};