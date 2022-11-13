/*
** EPITECH PROJECT, 2022
** Rtype [WSL : Ubuntu]
** File description:
** InGame
*/

#include "InGame.hpp"

InGame::InGame(): _key_pressed(NONE), _player(0, 0, 33, 17), _other(0, 51, 33, 17)
{
    initInGame();
}

InGame::~InGame() = default;

void InGame::handleOthers(Client &client)
{
    std::vector<Game::Player> others;

    for (auto other_pos : client.getOthersPos()) {
        _other.setPos(other_pos.first, other_pos.second);
        others.push_back(_other);
    }
    _others = others;
}

void InGame::handleAnimation(void)
{
    std::pair<int, int> player_rect = _player.getRectPositon();
    std::pair<int, int> other_rect = _other.getRectPositon();
    if (_player._player._clock.getElapsedTime() > sf::milliseconds(100)) {
        if (_signRect > 0) {
            _player.setRectPosition(player_rect.first + 33, 0);
            _other.setRectPosition(other_rect.first + 33, 51);
            if ((player_rect.first + 33) >= 132) {
                _signRect = -1;
            }
        } else {
            _player.setRectPosition(player_rect.first - 33, 0);
            _other.setRectPosition(other_rect.first - 33, 51);
            if ((player_rect.first - 33) <= 0) {
                _signRect = 1;
            }
        }
        _player._player._clock.restart();
    }
}

void InGame::handleInGame(sf::RenderWindow &window, State &state, Client &client)
{
    handleAnimation();
    if (_key_pressed != NONE) {
        client.sendData(_key_pressed);
    }
    _player.setPos(client.getPlayerPos().first, client.getPlayerPos().second);
    handleOthers(client);
    handleEvents(window, client);
    window.clear();
    displayInGame(window, state, client);
    window.display();
}

void InGame::displayInGame(sf::RenderWindow &window, State &state, Client &client)
{
    _background_paralax.update(Game::paralax::GAME_PARALAX);
    updateScore(1);
    _background_paralax.draw(window, Game::paralax::GAME_PARALAX);
    window.draw(_score_text._item);
    _player.draw(window);

    for (auto other : _others) {
        other.draw(window);
    }
    for (auto ennemy: client._ennemies) {
        ennemy.draw(window);
    }
}

void InGame::handleKeyPressed(sf::Event &event)
{
    if (_key_pressed != NONE) {
        return;
    }
    switch (event.key.code) {
        case (sf::Keyboard::Left):
            _key_pressed = LEFT;
            break;
        case (sf::Keyboard::Right):
            _key_pressed = RIGHT;
            break;
        case (sf::Keyboard::Up):
            _key_pressed = UP;
            break;
        case (sf::Keyboard::Down):
            _key_pressed = DOWN;
            break;
        default: break;
    }
}

void InGame::handleKeyReleased(sf::Event &event)
{
    switch (event.key.code) {
        // case sf::Keyboard::Escape:
        //     _state = PAUSE;
        //     break;
        case sf::Keyboard::Left:
            _key_pressed == LEFT ? _key_pressed = NONE : false;
            break;
        case sf::Keyboard::Right:
            _key_pressed == RIGHT ? _key_pressed = NONE : false;
            break;
        case sf::Keyboard::Up:
            _key_pressed == UP ? _key_pressed = NONE : false;
            break;
        case sf::Keyboard::Down:
            _key_pressed == DOWN ? _key_pressed = NONE : false;
            break;
        case sf::Keyboard::M:
            _score += 10;
            _score_text.SetText("Score " + std::to_string(_score));
            _score_text.setPos(10, 10);
            _score_text.setFontSize(40);
        // case sf::Keyboard::Space:
        //     _player.bullet_reset();
        //     break;
        default: break;
    }
}

void InGame::handleEvents(sf::RenderWindow &window, Client &client)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                handleKeyPressed(event);
                break;
            case sf::Event::KeyReleased:
                handleKeyReleased(event);
                break;
            case sf::Event::Closed:
                client.setCanReceiveData(false);
                window.close();
                break;
            default: break;
        }
    }
}

void InGame::initInGame()
{
    _signRect = 1;
    _background_paralax.setSprites(Game::paralax::GAME_PARALAX);
    _score = 0;
    _score_text = Game::Text("assets/menu/fonts/r-type.ttf");
    updateScore(0);
    _score_text.setPos(10, 10);
    _score_text.setFontSize(40);
}
