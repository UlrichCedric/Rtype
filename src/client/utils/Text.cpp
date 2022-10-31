/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak [WSL : Ubuntu-22.04]
** File description:
** Text
*/

#include "Text.hpp"

Text::Text(std::string path)
{
    _font.loadFromFile(Game::Config::ExecutablePath + path);
    _item.setFont(_font);
    _data = sf::String("");
    _item = sf::Text(_data, _font, 50);
}

void Text::SetText(std::string text)
{
    _data = sf::String(text);
    _item = sf::Text(_data, _font, 50);
}

void Text::setFont(std::string path)
{
    _font.loadFromFile(Game::Config::ExecutablePath + path);
    _item.setFont(_font);
}