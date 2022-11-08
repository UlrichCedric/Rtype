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
            void setPos(int x, int y) {_item.setPosition(x, y);};
            void SetText(std::string text);
            void setFont(std::string path);
            void setFontSize(int size) {_item.setCharacterSize(size);};
            void setFontColor(sf::Color color) {_item.setFillColor(color);};
            void setFontStyle(sf::Text::Style style) {_item.setStyle(style);};
            ~Text() {};
            sf::Font _font;
            sf::Text _item;
            sf::String _data;
        private:
    };
}
