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
#include "./Client.hpp"
#include <string>

class InGame {
    public:
    InGame();
    ~InGame() = default;

    void handleInGame(sf::RenderWindow &, State &, Client &);
    // Events / handle player input
    void handleEvents(sf::RenderWindow &, Client &);
    void handleKeyPressed(sf::Event &);
    void handleKeyReleased(sf::Event &);
    void initInGame(void);
    void setScore(int newScore) { _score = newScore; }
    int getScore(void) { return _score; }

    void drawScoreText(sf::RenderWindow &win) { _score_text.draw(win); }
    void drawButton(sf::RenderWindow &win) { win.draw(_button._image.getSprite()); }

    Menu::Button &getButton(void) { return _button; }
    Game::Text &getText(void) { return _score_text; }
    void displayInGame(sf::RenderWindow &, Client &);

    private:
    Game::Image _img;
    Game::Image _background;
    // Game::Player _player;
    // Music _music;
    Game::Paralax _background_paralax;
    enum Input _key_pressed = NONE;
    Menu::Button _button;
    // Game::Ennemy _ennemy;
    Game::Text _score_text;
    int _score;
};

#endif /* !INGAME_HPP_ */
