#pragma once

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

    std::pair<float, float> getTopLeft(void) { return { _posX, _posY }; }
    std::pair<float, float> getBottomLeft(void) { return { _posX, _posY + _sizeY }; }
    std::pair<float, float> getTopRight(void) { return { _posX + _sizeX, _posY }; }
    std::pair<float, float> getBottomRight(void) { return { _posX + _sizeX, _posY + _sizeY }; }
    std::pair<float, float> getMiddle(void) { return { _posX + (_sizeX / 2), _posY + (_sizeY / 2) }; }

    /**
     * @brief check if the given point is inside the hitbox
     *
     * @param pos the given point
     * @return true if the point is inside the hitbox
     * @return false if not
     */
    bool contains(std::pair<float, float> pos) { return betw(_posX, pos.first, _posX + _sizeX) && betw(_posY, pos.second, _posY + _sizeY); }

    /**
     * @brief check if the given point is inside the hitbox
     *
     * @param pos the given point
     * @return true if the point is inside the hitbox
     * @return false if not
     */
    bool contains(float x, float y) { return betw(_posX, x, _posX + _sizeX) && betw(_posY, y, _posY + _sizeY); }

    /**
     * @brief checks if the given hitbox touches this
     *
     * @param h2 the other hitbox
     * @return true if they touch
     * @return false if they do not
     */
    bool isCollidingWith(Hitbox &h2) {
        return (
            contains(h2.getTopLeft()) ||
            contains(h2.getTopRight()) ||
            contains(h2.getBottomLeft()) ||
            contains(h2.getBottomRight()) ||
            contains(h2.getMiddle())
        );
    }

    /**
     * @brief checks if the given hitbox touches this
     *
     * @param h2 the other hitbox
     * @return true if they touch
     * @return false if they do not
     */
    bool isCollidingWith(std::shared_ptr<Hitbox> h2) {
        return (
            contains(h2->getTopLeft()) ||
            contains(h2->getTopRight()) ||
            contains(h2->getBottomLeft()) ||
            contains(h2->getBottomRight()) ||
            contains(h2->getMiddle())
        );
    }

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

/**
 * @brief check if h1 and h2 touch each other
 *
 * @param h1 first hitbox
 * @param h2 second hitbox
 * @return true if at least one point of h2 is inside h1
 * @return false if they do not touch
 */
inline bool operator==(Hitbox& h1, Hitbox& h2) {
    return (
        h1.contains(h2.getTopLeft()) ||
        h1.contains(h2.getTopRight()) ||
        h1.contains(h2.getBottomLeft()) ||
        h1.contains(h2.getBottomRight()) ||
        h1.contains(h2.getMiddle())
    );
}

/**
 * @brief check if h1 and h2 do not touch each other
 *
 * @param h1 first hitbox
 * @param h2 second hitbox
 * @return true if at least one point of h2 is inside h1
 * @return false if they do not touch
 */
inline bool operator!=(Hitbox& h1, Hitbox& h2) {
    return !(
        h1.contains(h2.getTopLeft()) &&
        h1.contains(h2.getTopRight()) &&
        h1.contains(h2.getBottomLeft()) &&
        h1.contains(h2.getBottomRight()) &&
        h1.contains(h2.getMiddle())
    );
}