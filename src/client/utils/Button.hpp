/*
** EPITECH PROJECT, 2022
** rtype [WSL : Ubuntu-22.04]
** File description:
** Button
*/

#pragma once
#include "Image.hpp"

class Button {
    public:
        Button();
        bool IsClicked(sf::Vector2i mousePos);
        void IsHover(sf::Vector2i mousePos);
        ~Button();
        Image _image;
        sf::Color _color;
};
