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

    Factory(): _last_id(1) {
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

        for (auto mapNode: _customs) {
            std::cout << mapNode.first << std::endl;
            for (int i = 0; i < comp_nb; ++i) {
                if (!mapNode.second->has(i)) {
                    continue;
                }
                //TODO change this awful static cast
                auto comp = mapNode.second->getComponent(static_cast<components>(i)).get();
            }
        }
    }

    std::shared_ptr<Entity> createEntity(std::string name, std::size_t id = 0) {
        for (auto custom: _customs) {
            if (custom.first == name) {
                std::shared_ptr<Entity> e = std::make_shared<Entity>(*custom.second.get());
                if (e == nullptr) {
                    std::cout << "Failed to create entity " << name << std::endl;
                }
                try {
                    e.get()->setId(id == 0 ? _last_id++ : id);
                } catch (std::exception e) {
                    std::cerr << "Error : " << e.what() << std::endl;
                }
                return e;
            }
        }
        throw Error("Entity not found");
    }

    std::shared_ptr<Entity> getEntityById(std::size_t id) {
        for (auto custom: _customs) {
            if (custom.second.get()->getId() == id) {
                std::shared_ptr<Entity> e = std::make_shared<Entity>(*custom.second.get());
                if (e == nullptr) {
                    std::cerr << "Failed to get entity by id: " << id << std::endl;
                }
                return e;
            }
        }
        throw Error("Entity not found");
    }

    std::size_t getAvailableId(void) { return _last_id; }

    ~Factory() {  }

    private:

    std::size_t _last_id = 1;
    std::unordered_map<std::string, std::shared_ptr<Entity>> _customs;
};