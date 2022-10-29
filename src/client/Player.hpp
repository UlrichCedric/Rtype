/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak
** File description:
** Player
*/

#pragma once
#include "utils/Image.hpp"
#include "Config.hpp"
#include "Health.hpp"
#include "Shoot.hpp"

namespace Game {
    class Player {
        public:
            Player();
            ~Player();
            void setPos(float x, float y);
            void draw(sf::RenderWindow &window);
            void setLife(int life);
            void bullet_reset() { _shoot.setPos(_player.getPos().x + 33 , _player.getPos().y + 8);};
            sf::Vector2f getPos() {_pos = _player.getPos(); return _pos;};
            Image _player;
            Health _health;
            sf::Vector2f _pos;
            int _life = 100;
            Shoot _shoot;

    };
}
