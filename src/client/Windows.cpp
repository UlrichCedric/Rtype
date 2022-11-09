/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak [WSL : Ubuntu-22.04]
** File description:
** _windows
*/

#include "Windows.hpp"

#include <filesystem>

namespace Game {
    Windows::Windows() {
        _music.isRepeatable(true);
        _state = GAME;
        _in_game.setScore(0);
        _fps = 60;
        _key_pressed = NONE;
        _music.play();
    }

    void Windows::Display_pause()
    {
        _window.clear();
        _window.draw(_background.get_sprite());
        _window.display();
    }

    void Windows::init(void)
    {
        try {
            _window.create(sf::VideoMode(WIDTH, HEIGHT, 32), "R-Type");
            _window.setFramerateLimit(_fps);
        } catch (std::exception &e) {
            throw WindowCreationError();
        }
        return;
    }

    void Windows::Events()
    {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _state = END;
            } else if (event.type == sf::Event::MouseMoved) {
                _in_game.getButton().IsHover(sf::Mouse::getPosition(_window));
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (_in_game.getButton().IsClicked(sf::Mouse::getPosition(_window))) {
                        _state = GAME;
                    }
                }
            }
        }
    }

    void Windows::Display_menu()
    {
        _window.clear();
        _window.draw(_background.get_sprite());
        _in_game.drawButton(_window);
        _window.display();
    }

    void Windows::handleKeyPressed(sf::Event& event)
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

    void Windows::Events_game(void)
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

    void Windows::Events_pause(void)
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

    /**
     * @brief main menu loop
     *
     */
    void Windows::handleMenu(void)
    {
        Events();
        Display_menu();
    }

    /**
     * @brief main game loop
     *
     * @param client
     */
    void Windows::handleGame(Client &client)
    {
        Events_game();
        _window.clear();
        _in_game.drawScoreText(_window);

        for (auto img: client._images) {
            try {
                img->draw(_window);
            } catch (const std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }
        _window.display();
        _in_game.setScore(_in_game.getScore() + 1);
    }

    /**
     * @brief pause menu loop
     *
     */
    void Windows::handlePause(void)
    {
        Events_pause();
        Display_pause();
    }

    /**
     * @brief Main client loop
     *
     * @param client
     */
    void Windows::GameLoop(Client &client)
    {
        while (_window.isOpen()) {
            switch (_state) {
                case MENU: _menu.handleMenu(_window, _state); break;
                case GAME: _in_game.handleInGame(_window, _state); break;
                case END: _window.close(); break;
                default: break;
            }
        }
    }
}
