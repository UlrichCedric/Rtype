#include "../AComponent.hpp"
#include <utility>
#include <iostream>

/**
 * @brief This is a Movable point component
 * @id : movable
 */
class Movable: public AComponent {
    public:
    Movable(bool movable = true): _movable(movable) {  }
    std::string getName(void) { return "movable"; }
    int getEnum(void) { return MOVABLE; }
    void setMovable(bool movable) { _movable = movable; }
    ~Movable() {  }

    private:
    bool _movable;
};