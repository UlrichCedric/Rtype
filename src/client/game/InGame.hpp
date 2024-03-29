/*
** EPITECH PROJECT, 2022
** Rtype [WSL : Ubuntu]
** File description:
** InGame
*/

#ifndef INGAME_HPP_
#define INGAME_HPP_

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <string>

#include "../../Common.hpp"
#include "../utils/Image.hpp"
#include "../utils/Button.hpp"
#include "../utils/Text.hpp"
#include "../utils/Sound.hpp"
#include "../utils/Config.hpp"
#include "../utils/Music.hpp"
#include "../utils/Paralax.hpp"
#include "../game/Client.hpp"
#include "../menu/Menu.hpp"
#include "Player.hpp"
#include "Ennemy.hpp"

class InGame {
    public:
        InGame();
        ~InGame();

        void handleInGame(sf::RenderWindow &window, Menu::State_menu state, Client &client);
        void handleOthers(Client &client);
        void handleAnimation(void);
        //Events / handle player input
        void handleEvents(sf::RenderWindow &window, Client &client);
        void handleKeyPressed(sf::Event &event);

        enum Menu::State_menu getState () {return _state;} ;
        void handleKeyReleased(sf::Event &event, Client &client);
        void initInGame(void);
        void displayInGame(sf::RenderWindow &window, Client &);

        void updateScore(int addToScore) {
            _score += addToScore;
            _score_text.SetText("Score " + std::to_string(_score));
        }


    protected:
    private:
        Game::Image img;
        Game::Image background;
        Game::Player _player;
        Game::Player _other;
        std::vector<Game::Player> _others;
        // Music _music;
        Game::Paralax _background_paralax;
        enum Input _key_pressed;
        // Menu::Button _button;
        Game::Ennemy _ennemy;
        Game::Text _score_text;
        int _score;
        int _signRect;
        enum Menu::State_menu _state;
};

#endif /* !INGAME_HPP_ */
