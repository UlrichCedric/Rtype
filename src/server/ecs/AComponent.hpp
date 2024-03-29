#pragma once

#include "IComponent.hpp"
#include <memory>

class AComponent: public IComponent {
    public:
    AComponent() = default;
    AComponent(AComponent &) = default;
    ~AComponent() = default;
};
