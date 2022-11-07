/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak [WSL : Ubuntu-22.04]
** File description:
** _windows
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
        // img.setTexture(Config::ExecutablePath + "assets/background.jpg");
        // background.setTexture(Config::ExecutablePath + "assets/background_menu.jpg");
        // _music.isRepeatable(true);
        // _music.play();
        _key_pressed = NONE;
    }

    void Windows::Display_pause()
    {
        _window.clear();
        _window.draw(background.get_sprite());
        _window.display();
    }

    void Windows::init()
    {
        // try {
        //     _window.create(sf::VideoMode(WIDTH, HEIGHT, 32), "R-Type");
        //     _window.setFramerateLimit(fps);
        // } catch (std::exception &e) {
        //     throw WindowCreationError();
        // }
        // return;
    }

    void Windows::Events()
    {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _state = END;
            } else if (event.type == sf::Event::MouseMoved) {
                _button.IsHover(sf::Mouse::getPosition(_window));
		    } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (_button.IsClicked(sf::Mouse::getPosition(_window))) {
                        _state = GAME;
                    }
                }
            }
        }
    }

    void Windows::Display_menu()
    {
        _window.clear();
        // _window.draw(background.get_sprite());
        // _window.draw(_button._image.get_sprite());
        _window.display();
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
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _state = END;
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
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _state = END;
            } else if (event.type == sf::Event::KeyReleased) {
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

    void Windows::handleGame(Client &client)
    {
        Events_game();
        _window.clear();
        // paralax.update();
        // paralax.draw(_window);
        _window.draw(_text._item);
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
            img.draw(_window);
        }
        _window.display();
        _score += 2;
    }

    void Windows::handlePause(void)
    {
        Events_pause();
        Display_pause();
    }

    void Windows::handleEnd(void)
    {
        _window.close();
    }

    void Windows::Loop(Client &client)
    {
        // client.asyncReceiveData();
        while (_window.isOpen()) {
            // if (_key_pressed != NONE) {
            //     client.sendData(_key_pressed);
            // }
            // _player.setPos(client.getPlayerPos().first, client.getPlayerPos().second);
            // if (_state == END) {
            //     client.setCanReceiveData(false);
            // }
            switch (_state) {
                case MENU: _menu.handleMenu(_window); break;
                case GAME: handleGame(client); break;
                case PAUSE: handlePause(); break;
                case END: handleEnd(); break;
                default: break;
            }
            _score == 0 ? _text.SetText("Score : 0") : _text.SetText("Score : " + std::to_string(_score));
        }
        // _music.stop();
    }
}
