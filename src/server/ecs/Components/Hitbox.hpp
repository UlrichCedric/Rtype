#include "../AComponent.hpp"
#include "../constants.hpp"

/**
 * @brief This is a hitbox component
 *
 */
class Hitbox: public AComponent {
    public:

    Hitbox(void) = default;

    Hitbox(
        float sizeX,
        float size
    );

    Hitbox(Hitbox &h):
        _sizeX(h.getXSize()),
        _sizeY(h.getYSize()),
        _posX(h.getXPos()),
        _posY(h.getYPos())
    { }

    ~Hitbox(void) override = default;

    std::string getName(void) override { return "Hitbox"; }
    components getEnum(void) override { return HITBOX; }

    std::pair<float, float> getSize(void) { return { _sizeX, _sizeY }; }
    float getXSize(void) { return _sizeX; }
    float getYSize(void) { return _sizeY; }

    std::pair<float, float> getPos(void) { return { _posX, _posY }; }
    float getXPos(void) { return _posX; }
    float getYPos(void) { return _posY; }

    void setSize(float sizeX, float sizeY) {
        _sizeX = sizeX;
        _sizeY = sizeY;
    }

    void setSize(std::pair<float, float> size) {
        _sizeX = size.first;
        _sizeY = size.second;
    }

    void setXSize(float sizeX) { _sizeX = sizeX; }
    void setYSize(float sizeY) { _sizeY = sizeY; }

    void setPos(float posX, float posY) {
        _posX = posX;
        _posY = posY;
    }

    void setPos(std::pair<float, float> pos) {
        _posX = pos.first;
        _posY = pos.second;
    }

    void setXPos(float posX) { _posX = posX; }
    void setYPos(float posY) { _posY = posY; }

    private:
    float _sizeX;
    float _sizeY;
    float _posX;
    float _posY;
};