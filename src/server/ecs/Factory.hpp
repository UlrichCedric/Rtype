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

    Factory() {
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

        // If you wanna display every component of every template
        ////////////////////////////////////////////////////////////////
        // for (auto custom: _customs) {
        //     std::cout << custom.first << std::endl;
        //     for (int i = 0; strToInt[i].first != "NULL"; ++i) {
        //         if (custom.second->has(strToInt[i].second)) {
        //             std::cout << strToInt[i].first << std::endl;
        //         }
        //     }
        //     std::cout << "--------------------------------" << std::endl;
        // }
        ////////////////////////////////////////////////////////////////
    }

    std::shared_ptr<Entity> createEntity(std::string name, std::size_t id = 0) {
        for (auto custom: _customs) {
            if (custom.first != name) {
                continue;
                std::cout << name << " was not a " << custom.first << std::endl;
            }

            std::shared_ptr<Entity> e = std::make_shared<Entity>(*custom.second.get());

            if (e == nullptr) {
                throw Error("Failed to create entity");
            }

            try {
                e->setId(id == 0 ? _last_id : id);
                _last_id = e->getId() + 1;
            } catch (std::exception &e) {
                std::cerr << "Error : " << e.what() << std::endl;
            }
            return e;
        }
        throw Error("Entity not found");
    }

    std::shared_ptr<Entity> getEntityById(std::size_t id) {
        for (auto custom: _customs) {
            if (custom.second->getId() != id) {
                continue;
            }

            std::shared_ptr<Entity> e = std::make_shared<Entity>(*custom.second.get());

            if (e == nullptr) {
                std::cerr << "Failed to get entity by id: " << id << std::endl;
            }

            return e;
        }
        throw Error("Entity not found");
    }

    std::size_t getAvailableId(void) { return _last_id; }

    ~Factory() = default;

    private:

    std::size_t _last_id = 1;
    std::unordered_map<std::string, std::shared_ptr<Entity>> _customs;
};