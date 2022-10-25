#pragma once

#include "../AComponent.hpp"

class Uuid: public AComponent {
    public:
    Uuid(std::string uuid = "NULL"): _uuid(uuid) { }
    std::string getUuid(void) { return _uuid; }
    std::string getName(void) { return "uuid"; }
    ~Uuid(void) {  };

    private:
    std::string _uuid;
};