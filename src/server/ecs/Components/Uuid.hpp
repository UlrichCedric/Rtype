#pragma once

#include "../AComponent.hpp"
#include "../constants.hpp"

class Uuid: public AComponent {

    public:

    Uuid(std::string uuid = "NULL"): _uuid(uuid) {  }
    Uuid(Uuid &u): _uuid(u._uuid) {  }

    std::string getUuid(void) { return _uuid; }
    std::string getName(void) override { return "uuid"; }
    int getEnum(void) override { return UUID; }

    ~Uuid(void) {  };

    private:

    std::string _uuid;
};