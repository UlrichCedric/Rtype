/*
** EPITECH PROJECT, 2022
** Rtype [WSL: Ubuntu]
** File description:
** GameLobby
*/

#include "GameLobby.hpp"

GameLobby::GameLobby()
{
}

GameLobby::~GameLobby()
{
}

void GameLobby::initGameLobby(std::string game_state, std::string game_name, std::size_t game_nbr_players)
{
    _game_state = Text("assets/menu/fonts/r-type.ttf");
    _game_state.SetText(game_state);
    _game_state.setFontColor(sf::Color::White);
    _game_state.setFontSize(17);

    _game_name = Text("assets/menu/fonts/r-type.ttf");
    _game_name.SetText(game_name);
    _game_name.setFontColor(sf::Color::White);
    _game_name.setFontSize(17);

    std::string tmp = std::to_string(game_nbr_players);
    _game_nbr_players = Text("assets/menu/fonts/r-type.ttf");
    _game_nbr_players.SetText(tmp + "/4");
    _game_nbr_players.setFontColor(sf::Color::White);
    _game_nbr_players.setFontSize(17);

    _lobby_box.setSize(sf::Vector2f(840, 80));
    _lobby_box.setFillColor(sf::Color::Black);
    _lobby_box.setOutlineColor(sf::Color::White);
    _lobby_box.setOutlineThickness(2);
}

void GameLobby::setPosition(std::size_t index)
{
    _game_name.setPos(X_POS_LOBBY_BOX + 30, Y_POS_LOBBY_BOX + (index * 90) + 28);
    _game_state.setPos(X_POS_LOBBY_BOX + 560, Y_POS_LOBBY_BOX + (index * 90) + 28);
    _game_nbr_players.setPos(X_POS_LOBBY_BOX+ 750, Y_POS_LOBBY_BOX + (index * 90) + 28);
    _lobby_box.setPosition(X_POS_LOBBY_BOX, Y_POS_LOBBY_BOX + (index * 90));
}

void GameLobby::display(sf::RenderWindow &window)
{
    window.draw(_lobby_box);
    window.draw(_game_state._item);
    window.draw(_game_name._item);
    window.draw(_game_nbr_players._item);
}


