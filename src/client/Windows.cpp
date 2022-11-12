/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak [WSL : Ubuntu-22.04]
** File description:
** _windows
*/

#include "Windows.hpp"

namespace Game {
    Windows::Windows()
    {
        _state = MENU;
        fps = 60;
    }

    void Windows::init()
    {
        try {
            _window.create(sf::VideoMode(WIDTH, HEIGHT, 32), "R-Type");
            _window.setFramerateLimit(fps);
        } catch (std::exception &e) {
            throw WindowCreationError();
        }
        return;
    }

    void Windows::GameLoop(Client &client)
    {
        while (_window.isOpen()) {
            switch (_state) {
                case MENU: _menu.handleMenu(_window, _state, client); break;
                case GAME: _in_game.handleInGame(_window, _state, client); break;
                case END: client.setCanReceiveData(false); _window.close(); break;
                default: break;
            }
        }
    }
}