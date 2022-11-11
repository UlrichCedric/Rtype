/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak [WSL : Ubuntu-22.04]
** File description:
** Text
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


namespace Game {
    class Text {
        public:
            Text() {};
            Text(std::string path);
            /// @brief  set the position of the text
            void setPos(int x, int y) {_item.setPosition(static_cast<float>(x), static_cast<float>(y)); };
            /// @brief  set the the text
            void SetText(std::string text);
            /// @brief  set the the font
            void setFont(std::string path);
            /// @brief  set the the size of the text
            void setFontSize(int size) { _item.setCharacterSize(size); };
            /// @brief  set the the color of the text
            void setFontColor(sf::Color color) { _item.setFillColor(color); };
            /// @brief  set the the style of the text
            void setFontStyle(sf::Text::Style style) { _item.setStyle(style); };
            /// @brief get the Text object
            sf::Text &getText(void) { return _item; }
            /// @brief draw the text object to the given window
            void draw(sf::RenderWindow &win) { win.draw(_item); }

            ~Text() {};
            sf::Font _font;
            sf::Text _item;
            sf::String _data;
        private:
    };
}
