/*
** EPITECH PROJECT, 2022
** rtype [WSL : Ubuntu-22.04]
** File description:
** Button
*/

#include "Button.hpp"

// namespace Menu {
//     Button::Button()
//     {
//         _image.setTexture(Game::Config::ExecutablePath + "assets/button.jpg");
//         _image.setPos((WIDTH - 400) / 2, (HEIGHT - 200) / 2);
//         _image.setScale(0.5, 0.5);
//         _color = _image.getColor();
//     }

//     bool Button::IsClicked(sf::Vector2i mousePos)
//     {
//         if (_image.get_sprite().getGlobalBounds().contains(mousePos.x, mousePos.y))
//             return true;
//         return false;
//     }

//     void Button::IsHover(sf::Vector2i mousePos)
//     {
//         if (_image.get_sprite().getGlobalBounds().contains(mousePos.x, mousePos.y)) {
//             _image.setColor(sf::Color(255, 255, 255, 100));
//         }
//         _image.setColor(_color);
//     }
//     Button::~Button()
//     {
//     }
// }

void Button::setColorRect(COLOR_CODE fill_color, COLOR_CODE outline_color, float outline_thickness)
{
    if (fill_color == COLOR_CODE::BLACK) {
        _rect.setFillColor(sf::Color::Black);
    } else if (fill_color == COLOR_CODE::WHITE) {
        _rect.setFillColor(sf::Color::White);
    }
    if (outline_color == COLOR_CODE::BLACK) {
        _rect.setOutlineColor(sf::Color::Black);
    } else if (outline_color == COLOR_CODE::WHITE) {
        _rect.setOutlineColor(sf::Color::White);
    }
    _rect.setOutlineThickness(outline_thickness);
}

void Button::setText(std::string text)
{
    _data = sf::String(text);
    _item = sf::Text(_data, _font, 50);
}

void Button::setFont(std::string path)
{
    _font.loadFromFile(Game::Config::ExecutablePath + path);
    _item.setFont(_font);
}

void Button::setPos(int x, int y)
{
    _item.setPosition(x, y);
    _rect.setPosition(x - 10, y - 10);
}

void Button::draw(sf::RenderWindow &window)
{
    window.draw(_rect);
    window.draw(_item);
}
