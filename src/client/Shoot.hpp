/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak
** File description:
** Shoot
*/

#pragma once
#include "Image.hpp"

namespace Game {
    class Shoot {
        public:
            Shoot();
            void setPos(float x, float y);
            void draw(sf::RenderWindow &window) {window.draw(_bullet.get_sprite());};
            sf::Vector2f getPos() {return _bullet.getPos();};
            ~Shoot();
            Image _bullet;
    };
}
