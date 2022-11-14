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
        _state = Menu::State_menu::MENU;
        _fps = 60;
        _game_start = false;
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

    void Windows::GameLoop(Client &client)
    {
        while (_window.isOpen()) {
            switch (_state) {
                case Menu::State_menu::MENU : _menu.handleMenu(_window, _state, client); break;
                case Menu::State_menu::LOSE: _menu.handleMenu(_window, _state, client); break;
                case Menu::State_menu::GAME: std::cout << "prout" << std::endl; _in_game.handleInGame(_window, _state, client); break;
                case Menu::State_menu::CLOSE: client.setCanReceiveData(false); _window.close(); break;
                case Menu::State_menu::PAUSE: _menu.handleMenu(_window, _state, client); break;
                case Menu::State_menu::SETTINGS: _menu.handleMenu(_window, _state, client); break;
                case Menu::State_menu::LOBBY: _menu.handleMenu(_window, _state, client); break;
                default: break;
            }
            if (_menu.getState() == Menu::State_menu::CLOSE)
                _window.close();
            std::cout << "State : " << _state << std::endl;
            if (_state == Menu::State_menu::GAME)
                _state = _in_game.getState();
            else
                _state = _menu.getState();
            _fps = _menu.getFps();
        }
    }
}
