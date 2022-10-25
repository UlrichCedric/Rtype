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
            std::shared_ptr<Entity> e = std::make_shared<Entity>();

            while (stream >> word) {
                if (word.empty()) {
                    break;
                }
                for (auto _str: strToInt) {
                    if (word == _str.first) {
                        e.get()->addComponent(_str.second);
                        break;
                    }
                }
            }

            _customs.insert(std::make_pair(name, std::make_shared<Entity>(*e)));
        }

        for (auto entity: _customs) {
            for (int i = 0; i < comp_nb; ++i) {
                auto comp = entity.second->getComponent(i).get();
                if (comp == nullptr) {
                    continue;
                }
            }
        }
    }

    std::shared_ptr<Entity> createEntity(std::string name) {
        for (auto custom: _customs) {
            if (custom.first == name) {
                std::shared_ptr<Entity> e = std::make_shared<Entity>(*(custom.second));
                e.get()->setId(_last_id);
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
