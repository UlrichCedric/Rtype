#pragma once

#include <iostream>

class IComponent {
    public:
    virtual ~IComponent() = default;
    virtual std::string getName(void) = 0;
    virtual int getEnum(void) = 0;
};
