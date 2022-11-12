/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak
** File description:
** Player
*/

#include "Player.hpp"

namespace Game {
    Player::Player(int x, int y, int width, int height) {
        _width = width;
        _height = height;
        _rectPos = {x, y};
        _player.setTexture(Config::ExecutablePath + "assets/player.png");
        _player.setScale(3.0, 3.0);
        _player.setPos(100, 100);
        _player.setRect(x, y, width, height);
        _health = Health({60, 10}, 0, 0, 100);
    }

    void Player::setPos(float x, float y) {
        _player.setPos(x, y);
        _pos = _player.getPos();
        _health.update(x, y, _life);
    }

    void Player::setRectPosition(int x, int y)
    {
        _rectPos = {x, y};
        _player.setRect(x, y, _width, _height);
    }

    std::pair<int, int> Player::getRectPositon(void)
    {
        return _rectPos;
    }

    void Player::draw(sf::RenderWindow &window) {
        window.draw(_player.get_sprite());
        _health.draw(window);
    }

    void Player::setLife(int life) {
        _life = life;
        _health.update(_pos.x, _pos.y, _life);
    }

    Player::~Player() = default;
}
