/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak [WSL : Ubuntu-22.04]
** File description:
** Windows
*/

#include "Windows.hpp"

namespace Game {
    Windows::Windows()
    {
        _state = MENU;
        fps = 60;
        _score = 0;
        _text = Text("assets/police.ttf");
        _text.SetText("Score : 0");
        _text.setPos(0, 0);
        _text.setFontSize(50);
        img.setTexture(Config::ExecutablePath + "assets/background.jpg");
        background.setTexture(Config::ExecutablePath + "assets/background_menu.jpg");
        _music.isRepeatable(true);
        _music.play();
        _key_pressed = NONE;
    }

    void Windows::Display_pause()
    {
        window.clear();
        window.draw(background.get_sprite());
        window.display();
    }

    void Windows::init()
    {
        try {
            window.create(sf::VideoMode(WIDTH, HEIGHT, 32), "R-Type");
            window.setFramerateLimit(fps);
        } catch (std::exception &e) {
            throw WindowCreationError();
        }
        return;
    }

    void Windows::Events()
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } if (event.type == sf::Event::MouseMoved) {
                _button.IsHover(sf::Mouse::getPosition(window));
		    } if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (_button.IsClicked(sf::Mouse::getPosition(window))) {
                        _state = GAME;
                    }
                }
            }
        }
    }

    void Windows::Display_menu()
    {
        window.clear();
        window.draw(background.get_sprite());
        window.draw(_button._image.get_sprite());
        window.display();
    }

    void Windows::handleKeyPressed(sf::Event& event)
    {
        if (_key_pressed != NONE) {
            return;
        }
        switch (event.key.code) {
            case sf::Keyboard::Left:
                _key_pressed = LEFT;
                break;
            case sf::Keyboard::Right:
                _key_pressed = RIGHT;
                break;
            case sf::Keyboard::Up:
                _key_pressed = UP;
                break;
            case sf::Keyboard::Down:
                _key_pressed = DOWN;
                break;
            default: break;
        }
    }

    void Windows::handleKeyReleased(sf::Event& event)
    {
        switch (event.key.code) {
            case sf::Keyboard::Escape:
                _state = PAUSE;
                break;
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
            case sf::Keyboard::Space:
                _player.bullet_reset();
                break;
            default: break;
        }
    }

    void Windows::Events_game()
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            switch (event.type) {
                case sf::Event::KeyPressed:
                    handleKeyPressed(event);
                    break;
                case sf::Event::KeyReleased:
                    handleKeyReleased(event);
                    break;
                default: break;
            }
        }
    }

    void Windows::Events_pause()
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Escape) {
                    _state = GAME;
                }
            }
        }
    }

    void Windows::handleMenu(void)
    {
        Events();
        Display_menu();
    }

    void Windows::handleGame(void)
    {
        Events_game();
        window.clear();
        paralax.update();
        paralax.draw(window);
        window.draw(_text._item);
        _player.draw(window);
        _player._shoot.setPos(_player._shoot.getPos().x + 25, _player._shoot.getPos().y);
        _player._shoot.draw(window);
        _ennemy.run();
        _ennemy.draw(window);
        if (_ennemy._ennemy.get_sprite().getGlobalBounds().contains(_player._shoot.getPos().x, _player._shoot.getPos().y)) {
            _ennemy.respawn();
            _player.bullet_reset();
            _score += 1;
        }
        if (_ennemy._ennemy.get_sprite().getGlobalBounds().contains(_player.getPos().x, _player.getPos().y)) {
            _player.setLife(_player._health.getHealth() - 10);
            if (_player._health.getHealth() <= 0) {
                _state = MENU;
                _player.setLife(100);
            }
        }
        window.display();
        _score += 2;
    }

    void Windows::handlePause(void)
    {
        Events_pause();
        Display_pause();
    }

    void Windows::handleEnd(void)
    {
        window.close();
    }

    void Windows::Loop(Client &client)
    {
        client.asyncSendData(NONE);
        client.asyncReceiveData();
        while (window.isOpen()) {
            if (_key_pressed != NONE) {
                client.asyncSendData(_key_pressed);
            }
            client.receiveData();
            _player.setPos(client.getPlayerPos().first, client.getPlayerPos().second);
            switch (_state) {
                case MENU: handleMenu(); break;
                case GAME: handleGame(); break;
                case PAUSE: handlePause(); break;
                case END: handleEnd(); break;
                default: break;
            }
            _score == 0 ? _text.SetText("Score : 0") : _text.SetText("Score : " + std::to_string(_score));
        }
        _music.stop();
    }
}
