/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak
** File description:
** Player
*/

#pragma once
#include "../utils/Image.hpp"
#include "../utils/Config.hpp"
#include "../game/Health.hpp"
#include "../game/Shoot.hpp"

namespace Game {
    class Player {
        public:
            Player(int x, int y, int width, int height);

            void setPos(float x, float y);
            void setRectPosition(int x, int y);
            std::pair<int, int> getRectPositon(void);
            void draw(sf::RenderWindow &window);
            void setLife(int life);
            void setHp(int hp, std::pair<float, float> coords) { _health.update(coords.first, coords.second, hp); };
            void bullet_reset() { _shoot.setPos(_player.getPos().x + 33 , _player.getPos().y + 8);};
            sf::Vector2f getPos() {_pos = _player.getPos(); return _pos;};

            ~Player(void);

            Image _player;
            Health _health;
            sf::Vector2f _pos;
            int _life = 100;
            Shoot _shoot;
        private:
            int _width;
            int _height;
            std::pair<int, int> _rectPos;
    };
}
