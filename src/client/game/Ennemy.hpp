/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak
** File description:
** Ennemy
*/

#pragma once
#include "../utils/Image.hpp"

namespace Game {
    class Ennemy {
        public:
            Ennemy();
            Ennemy(
                std::size_t id,
                std::string path,
                std::pair<float, float> coords,
                std::pair<float, float> scale,
                std::pair<float, float> rectSize,
                int health
            ) {
                _ennemy = Image(id, path, coords, scale, rectSize, health);
                setPos(coords.first, coords.second);
            }
            void setPos(float x, float y) { _ennemy.setPos(x, y); };
            void respawn() { _ennemy.setPos(1400, 500); };
            void run();
            void draw(sf::RenderWindow &window) { window.draw(_ennemy.get_sprite()); };

            ~Ennemy();

            private:
            Image _ennemy;
    };
}
