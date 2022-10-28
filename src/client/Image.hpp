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
#include <exception>
#include <iostream>
#include "../Errors.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Config.hpp"

#define WIDTH 1280
#define HEIGHT 720
namespace Game {
    class Image {
        public:
            Image() {};
            void setTexture(std::string  path);
            std::string &get_path() { return _path; }
            void set_path(std::string path) { _path = path; }
            sf::Sprite &get_sprite() { return _sprite; }
            void setPos(float posX = 0, float posY = 0) { _sprite.setPosition(posX, posY); };
            void setScale(float scaleX = 1, float scaleY = 1) { _sprite.setScale(scaleX, scaleY); };
            sf::Vector2f getPos() { return _sprite.getPosition(); };
            sf::Color getColor() { return _sprite.getColor(); };
            void setColor(sf::Color color) { _sprite.setColor(color); };
            void setRotation(float angle) { _sprite.setRotation(angle); };
            void setRect(int x, int y, int width, int height) { _sprite.setTextureRect(sf::IntRect(x, y, width, height)); };
            void MoveRect(int x, int y, int width, int height) { _sprite.setTextureRect(sf::IntRect(x, y, width, height)); };
            ~Image() {};
        private:
            std::string _path;
            sf::Texture _texture;
            sf::Sprite _sprite;
            sf::IntRect _rect;
            int _rectL;
            int _rectR;
            int _posx;
            int _posy;
            size_t id;
    };
};
