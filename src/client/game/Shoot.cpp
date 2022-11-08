/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak
** File description:
** Shoot
*/

#include "Shoot.hpp"

namespace Game {
    Shoot::Shoot() 
    {
        _bullet.setTexture("assets/sprites/bullet.png");
        _bullet.setScale(1.0, 1.0);
        _bullet.setRect(0, 0, 17, 18);
    }

    Shoot::~Shoot() {}

    void Shoot::setPos(float x, float y) {
        _bullet.setPos(x, y);
    }
}

