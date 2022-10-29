/*
** EPITECH PROJECT, 2022
** Rtype [WSL : Ubuntu]
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu::Menu()
{
    _state = State_menu::MENU;
    _title.setTexture(Game::Config::ExecutablePath + "assets/background_menu.jpg");
}

Menu::Menu::~Menu()
{
}

void Menu::Menu::handleEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        // if (event.type == sf::Event::Closed) {
        //     _state = END;
        // } else if (event.type == sf::Event::MouseMoved) {
        //     // _button.IsHover(sf::Mouse::getPosition(window));
        // } else if (event.type == sf::Event::MouseButtonPressed) {
        //     if (event.mouseButton.button == sf::Mouse::Left) {
        //         if (_button.IsClicked(sf::Mouse::getPosition(window))) {
        //             _state = GAME;
        //         }
        //     }
        // }
    }
}

void Menu::Menu::handleMenu(sf::RenderWindow &window)
{
    window.clear();
    window.draw(_title.get_sprite());
    // switch (_state) {
    //     case MENU: displayMenu(window); break;
    //     case LOBBY: break;
    //     case SETTINGS: break;
    //     case GAME: break;
    //     default: break;
    // }
    window.display();
}

void Menu::Menu::displayMenu(sf::RenderWindow &window)
{
    // this->handleEvents(window);
    window.draw(_title.get_sprite());
    // window.draw(background.get_sprite());
    // window.draw(_button._image.get_sprite());
}

