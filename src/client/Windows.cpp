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
        _fps = 60;
    }

    void Windows::init()
    {
        try {
            _window.create(sf::VideoMode(WIDTH, HEIGHT, 32), "R-Type");
            _window.setFramerateLimit(_fps);
        } catch (std::exception &e) {
            throw WindowCreationError();
        }
        return;
    }

    // void Windows::Events()
    // {
        // sf::Event event;
        // while (_window.pollEvent(event)) {
        //     if (event.type == sf::Event::Closed) {
        //         _state = END;
        //     } else if (event.type == sf::Event::MouseMoved) {
        //         _button.IsHover(sf::Mouse::getPosition(_window));
		//     } else if (event.type == sf::Event::MouseButtonPressed) {
        //         if (event.mouseButton.button == sf::Mouse::Left) {
        //             if (_button.IsClicked(sf::Mouse::getPosition(_window))) {
        //                 _state = GAME;
        //             }
        //         }
        //     }
        // }
    // }

    void Windows::GameLoop ()//Client &client)
    {
        while (_window.isOpen()) {
            switch (_state) {
                case MENU: _menu.handleMenu(_window, _state); break;
                case GAME: _in_game.handleInGame(_window, _state); break;
                case END: _window.close(); break;
                default: break;
            }
            if (_menu.getState() == Menu::State_menu::CLOSE)
                _window.close();
            _fps = _menu.getFps();
        }
    }
}
