/*
** EPITECH PROJECT, 2022
** rtype [WSL : Ubuntu-22.04]
** File description:
** Button
*/

#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <exception>
#include <iostream>
#include "../../Errors.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Config.hpp"

// namespace Menu {
//     class Button {
//         public:
//             Button();
//             bool IsClicked(sf::Vector2i mousePos);
//             void IsHover(sf::Vector2i mousePos);
//             ~Button();
//             Game::Image _image;
//             sf::Color _color;
//     };
// }

class Button {
    public:
        enum COLOR_CODE {
            BLACK = 0,
            WHITE = 1,
        };
        Button() {};
        ~Button() {};
        /// @brief set the color of rect behind
        void setColorRect(COLOR_CODE fill_color, COLOR_CODE outline_color, float outline_thickness);
        /// @brief  set the position of the text
        void setPos(int x, int y);
        /// @brief  set the the text
        void setText(std::string text);
        /// @brief  set the the font
        void setFont(std::string path);
        /// @brief  set the the size of the text
        void setFontSize(int size) {_item.setCharacterSize(size); _rect.setSize(sf::Vector2f(_data.getSize() * 17 + 20, size + 20));};
        /// @brief  set the the color of the text
        void setFontColor(sf::Color color) {_item.setFillColor(color);};
        /// @brief  set the the style of the text
        void setFontStyle(sf::Text::Style style) {_item.setStyle(style);};
        /// @brief  draw the text with the rect behind
        void draw(sf::RenderWindow &window);
    private:
        sf::Font _font;
        sf::Text _item;
        sf::String _data;
        sf::RectangleShape _rect;
    };
