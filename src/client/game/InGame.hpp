/*
** EPITECH PROJECT, 2022
** Rtype [WSL : Ubuntu]
** File description:
** InGame
*/

#ifndef INGAME_HPP_
#define INGAME_HPP_

#include "../../Common.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include "../utils/Image.hpp"
#include "../utils/Button.hpp"
#include "../utils/Text.hpp"
#include "../utils/Sound.hpp"
#include "../utils/Config.hpp"
#include "../utils/Music.hpp"
#include "../utils/Paralax.hpp"
#include <string>

class InGame {
    public:
        InGame();
        ~InGame();

        void handleInGame(sf::RenderWindow &window, State &state);
        //Events / handle player input
        void handleEvents(sf::RenderWindow &window);
        void handleEventsMovementPlayer(sf::Event &event);
        void handleEventsOthers(sf::Event &event);
        void initInGame();
        void displayInGame(sf::RenderWindow &window);


    protected:
    private:
        Game::Image img;
        Game::Image background;
        // Game::Player _player;
        // Music _music;
        Game::Paralax _background_paralax;
        enum Input _key_pressed;
        Menu::Button _button;
        // Game::Ennemy _ennemy;
        Game::Text _score_text;
        int _score;
};

#endif /* !INGAME_HPP_ */
