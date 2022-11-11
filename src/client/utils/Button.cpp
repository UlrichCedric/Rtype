/*
** EPITECH PROJECT, 2022
** rtype [WSL : Ubuntu-22.04]
** File description:
** Button
*/

#include "Button.hpp"

namespace Menu {
    Button::Button()
    {
        _image.setTexture(Game::Config::ExecutablePath + "assets/button.jpg");
        _image.setPos((WIDTH - 400) / 2, (HEIGHT - 200) / 2);
        _image.setScale(0.5, 0.5);
        _color = _image.getColor();
    }

    bool Button::IsClicked(sf::Vector2i mousePos)
    {
        if (_image.get_sprite().getGlobalBounds().contains(mousePos.x, mousePos.y))
            return true;
        return false;
    }

    void Button::IsHover(sf::Vector2i mousePos)
    {
        if (_image.get_sprite().getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            _image.setColor(sf::Color(255, 255, 255, 100));
        }
        _image.setColor(_color);
    }
    Button::~Button()
    {
    }
}
