/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak
** File description:
** Ennemy
*/

#include "Ennemy.hpp"

namespace Game {
    Ennemy::Ennemy()
    {
        _ennemy.setTexture(Config::ExecutablePath + "assets/sprites/enemy.gif");
        _ennemy.setPos(1100, 500);
        _ennemy.setRect(0, 0, 168, 209);
        _ennemy.setScale(0.5, 0.5);
    }

    void Ennemy::run()
    {
        if (_ennemy.getPos().x > 0)
            _ennemy.setPos(_ennemy.getPos().x - 10, _ennemy.getPos().y);
        else if (_ennemy.getPos().x > 1280) {
            _ennemy.setPos(1200, rand() % 600);
        } else {
            _ennemy.setPos(1200, rand() % 600   );
        }
    }

    Ennemy::~Ennemy()
    {
    }
}
