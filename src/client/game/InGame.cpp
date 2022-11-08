/*
** EPITECH PROJECT, 2022
** Rtype [WSL : Ubuntu]
** File description:
** InGame
*/

#include "InGame.hpp"

InGame::InGame()
{
    initInGame();
}

InGame::~InGame()
{
}

void InGame::handleInGame(sf::RenderWindow &window, State &state)
{
    handleEvents(window);
    window.clear();
    displayInGame(window);
    window.display();
    // _score == 0 ? _text.SetText("Score : 0") : _text.SetText("Score : " + std::to_string(_score));
}

void InGame::displayInGame(sf::RenderWindow &window)
{
    _background_paralax.update(Game::paralax::GAME_PARALAX);
    _background_paralax.draw(window, Game::paralax::GAME_PARALAX);
    window.draw(_score_text._item);
    // paralax.update();
        // paralax.draw(_window);
        // _player.draw(_window);
        // _player._shoot.setPos(_player._shoot.getPos().x + 25, _player._shoot.getPos().y);
        // _player._shoot.draw(_window);
        // _ennemy.run();
        // _ennemy.draw(_window);
        // if (_ennemy._ennemy.get_sprite().getGlobalBounds().contains(_player._shoot.getPos().x, _player._shoot.getPos().y)) {
        //     _ennemy.respawn();
        //     _player.bullet_reset();
        //     _score += 1;
        // }
        // if (_ennemy._ennemy.get_sprite().getGlobalBounds().contains(_player.getPos().x, _player.getPos().y)) {
        //     _player.setLife(_player._health.getHealth() - 10);
        //     if (_player._health.getHealth() <= 0) {
        //         _state = MENU;
        //         _player.setLife(100);
        //     }
        // }
        // for (auto img: client._images) {
        //     img.draw(_window);
        // }
}

void InGame::handleEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Escape) {
                _score += 1;
                _score_number.SetText(std::to_string(_score));
            }
        }
    }
}


void InGame::initInGame()
{
    _background_paralax.setSprites(Game::paralax::GAME_PARALAX);
    _score = 0;
    _score_text = Game::Text("assets/menu/fonts/r-type.ttf");
    _score_text.SetText("Score : ");
    _score_text.setPos(10, 10);
    _score_text.setFontSize(40);
    _score_number = Game::Text("assets/menu/fonts/r-type.ttf");
    _score_number.SetText(std::to_string(_score));
    _score_number.setPos(150, 10);
    _score_number.setFontSize(40);
}
