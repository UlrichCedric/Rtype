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
    _title.setTexture(Game::Config::ExecutablePath + "assets/menu/R-TYPE_title.png");
    _title.setPos(0, 460);
    _text_bottom_right = Text("assets/menu/font/r-type.ttf");
    _text_top_right01 = Text("assets/menu/font/r-type.ttf");
    _text_top_right02 = Text("assets/menu/font/r-type.ttf");
    _text_bottom_right.SetText("Epitech project 2022");
    _text_bottom_right.setFontSize(20);
    _text_bottom_right.setPos(500, 600);
    _text_top_right01.SetText("BLAST OFF AND STRIKE");
    _text_top_right01.setFontSize(20);
    _text_top_right01.setPos(500, 0);
    _text_top_right02.SetText("THE EVIL BYDO EMPIRE!");
    _text_top_right02.setFontSize(20);
    _text_top_right02.setPos(500, 100);
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
    switch (_state) {
        case MENU: displayMenu(window); break;
        case LOBBY: break;
        case SETTINGS: break;
        case GAME: break;
        default: break;
    }
    window.display();
}

void Menu::Menu::displayMenu(sf::RenderWindow &window)
{
    // this->handleEvents(window);
    window.draw(_title.get_sprite());
    window.draw(_text_bottom_right._item);
    window.draw(_text_top_right01._item);
    window.draw(_text_top_right02._item);
}

