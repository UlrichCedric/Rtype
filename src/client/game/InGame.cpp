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

    // Sets default score text
    _score_text = Game::Text("assets/police.ttf");
    _score_text.SetText("Score : 0");
    _score_text.setPos(0, 0);
    _score_text.setFontSize(50);
}

InGame::~InGame() = default;

void InGame::handleInGame(sf::RenderWindow &window, State &state, Client &client)
{
    handleEvents(window);
    if (_key_pressed != NONE) {
        client.sendData(_key_pressed);
    }
    // _player.setPos(client.getPlayerPos().first, client.getPlayerPos().second);
    // if (_state == END) {
    //     client.setCanReceiveData(false);
    // }
    window.clear();
    displayInGame(window, client);
    window.display();
    _score_text.SetText("Score : " + std::to_string(_score));
}

void InGame::displayInGame(sf::RenderWindow &window, Client &client)
{
    _background_paralax.update(Game::paralax::GAME_PARALAX);
    _background_paralax.draw(window, Game::paralax::GAME_PARALAX);
    window.draw(_score_text._item);
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
    for (auto img: client._images) {
        img->draw(window);
    }
}

void InGame::handleEventsOthers(sf::Event &event)
{
    if (event.key.code == sf::Keyboard::M) {
        _score += 10;
        _score_text.SetText("Score " + std::to_string(_score));
        _score_text.setPos(10, 10);
        _score_text.setFontSize(40);
    }
}

void InGame::handleEventsMovementPlayer(sf::Event &event)
{
    switch (event.key.code) {
        case sf::Keyboard::Up:
            _key_pressed = UP;
            break;
        case sf::Keyboard::Down:
            _key_pressed = DOWN;
            break;
        case sf::Keyboard::Left:
            _key_pressed = LEFT;
            break;
        case sf::Keyboard::Right:
            _key_pressed = RIGHT;
            break;
        case sf::Keyboard::Space:
            _key_pressed = SPACE;
            break;
        default: break;
    }
}

void InGame::handleEvents(sf::RenderWindow &window)
{
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        switch (event.type) {
            case sf::Event::KeyPressed:
                handleEventsMovementPlayer(event);
                break;
            case sf::Event::KeyReleased:
                handleEventsOthers(event);
                break;
            case sf::Event::Closed:
                window.close();
                break;
            default: break;
        }
    }
}


void InGame::initInGame()
{
    _background_paralax.setSprites(Game::paralax::GAME_PARALAX);
    _score = 0;
    _score_text = Game::Text("assets/menu/fonts/r-type.ttf");
    _score_text.SetText("Score " + std::to_string(_score));
    _score_text.setPos(10, 10);
    _score_text.setFontSize(40);
}
