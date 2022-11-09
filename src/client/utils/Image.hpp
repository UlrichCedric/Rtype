/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak [WSL : Ubuntu-22.04]
** File description:
** Image
*/

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <exception>

#include "../game/Health.hpp"
#include "../../Errors.hpp"
#include "Config.hpp"

static const constexpr int WIDTH = 1280;
static const constexpr int HEIGHT = 720;

// class Game::Health;
class Health;

namespace Game {
    class Image {
        public:
            Image() = default;
            Image(const Image &) = default;
            Image(
                std::size_t id,
                std::string path,
                std::pair<float, float> pos,
                std::pair<float, float> scale,
                std::pair<float, float> rect,
                int health
            );

            void setTexture(std::string path);
            std::string &get_path() { return _path; }
            void set_path(std::string path) { _path = path; }
            sf::Sprite &get_sprite() { return _sprite; }
            void setPos(float posX = 0, float posY = 0) { _sprite.setPosition(posX, posY); }
            void setPos(std::pair<float, float> pos) {
                _sprite.setPosition(pos.first, pos.second);
            }

            void setHp(int hp, std::pair<float, float> coords) {
                if (!_isHealth) {
                    throw Error("Couldn't find image health");
                }
                _health.update(coords.first, coords.second, hp);
            }

            void setScale(float scaleX = 1, float scaleY = 1) { _sprite.setScale(scaleX, scaleY); };
            void setScale(std::pair<float, float> scale) { _sprite.setScale(scale.first, scale.second); };

            sf::Vector2f getPos() { return _sprite.getPosition(); };
            sf::Color getColor() { return _sprite.getColor(); };
            void setColor(sf::Color color) { _sprite.setColor(color); };
            void setRotation(float angle) { _sprite.setRotation(angle); };
            void setRect(int left, int top, int width, int height) {
                _sprite.setTextureRect(sf::IntRect(left, top, width, height));
                std::cout << "rectangle x: " << width << " y: " << height << std::endl;
            };
            void MoveRect(int x, int y, int width, int height) { _sprite.setTextureRect(sf::IntRect(x, y, width, height)); };
            std::size_t getId(void) { return _id; }
            void draw(sf::RenderWindow &win) { win.draw(_sprite); }
            ~Image() = default;

        private:
            size_t _id;
            std::string _path;
            sf::Texture _texture;
            sf::Sprite _sprite;
            sf::IntRect _rect;
            float _rectX;
            float _rectY;

            /**
             * @brief if true then display lifebar
             *
             */
            bool _isHealth;
            Game::Health _health;
            bool _isAlive;
            int _scene;
    };
}