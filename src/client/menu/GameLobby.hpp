/*
** EPITECH PROJECT, 2022
** Rtype [WSL: Ubuntu]
** File description:
** GameLobby
*/

#pragma once

#include "../utils/Image.hpp"
#include "../utils/Text.hpp"


class GameLobby {
    public:
        GameLobby();
        ~GameLobby();
        void initGameLobby(std::string game_state, std::string game_name, std::size_t _game_nbr_players);
        void setPosition(std::size_t index);
        void display(sf::RenderWindow &window);

    protected:
    private:
        #define X_POS_LOBBY_BOX 215
        #define Y_POS_LOBBY_BOX 205
        Game::Text _game_state;
        Game::Text _game_name;
        Game::Text _game_nbr_players;
        sf::RectangleShape _lobby_box;

};
