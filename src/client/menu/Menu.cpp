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
    _selection = 0;
    _title.setTexture(Game::Config::ExecutablePath + "assets/menu/R-TYPE_title.png");
    _title.setPos(15, 430);
    // Load Fonts
    _text_bottom_right = Text("assets/menu/font/r-type.ttf");
    _text_multiplayer = Text("assets/menu/font/r-type.ttf");
    _text_settings = Text("assets/menu/font/r-type.ttf");
    _text_top_right01 = Text("assets/menu/font/r-type.ttf");
    _text_top_right02 = Text("assets/menu/font/r-type.ttf");
    //_text_top_right01
    _text_top_right01.SetText("BLAST OFF AND STRIKE");
    _text_top_right01.setFontSize(20);
    _text_top_right01.setPos(830, 15);
    //_text_top_right02
    _text_top_right02.SetText("THE EVIL BYDO EMPIRE!");
    _text_top_right02.setFontSize(20);
    _text_top_right02.setPos(830, 45);
    //_text_multiplayer
    _text_multiplayer.SetText("MULTIPLAYER");
    _text_multiplayer.setFontSize(30);
    _text_multiplayer.setFontColor(sf::Color::Black);
    _text_multiplayer.setFontStyle(sf::Text::Bold);
    _text_multiplayer.setPos(920, 180);
    //_text_settings
    _text_settings.SetText("SETTINGS");
    _text_settings.setFontSize(30);
    _text_settings.setPos(995, 270);
    //_text_bottom_right
    _text_bottom_right.SetText("Epitech project 2022");
    _text_bottom_right.setFontSize(20);
    _text_bottom_right.setPos(835, 670);
    //_rect_selection
    _rect_selection.setTexture(Game::Config::ExecutablePath + "assets/menu/white_rect.jpg");
    _rect_selection.setRect(0, 0, 365, 56);
    _rect_selection.setPos(905, 169);
}

Menu::Menu::~Menu()
{
}

void Menu::Menu::handleEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        // if (event.type == sf::Event::KeyPressed) {
        //     if (event.key.code == sf::Keyboard::Up) {
        //         if (_selection == 1) {
        //             _selection = 0;
        //             _rect_selection.setRect(0, 0, 327, 56);
        //             _rect_selection.setPos(900, 175);
        //             _text_multiplayer.setFontStyle(sf::Text::Bold);
        //             _text_multiplayer.setFontColor(sf::Color::Black);
        //         }
        //     }
        //     else if (event.key.code == sf::Keyboard::Down) {
        //         if (_selection == 0) {
        //             _selection = 1;
        //             _rect_selection.setRect(0, 0, 267, 56);
        //             _rect_selection.setPos(995, 2650);
        //             _text_settings.setFontStyle(sf::Text::Bold);
        //             _text_settings.setFontColor(sf::Color::Black);
        //         }
        //     }
        // }
    }
}

void Menu::Menu::handleMenu(sf::RenderWindow &window)
{
    this->handleEvents(window);
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
    window.draw(_title.get_sprite());
    window.draw(_rect_selection.get_sprite());
    window.draw(_text_top_right01._item);
    window.draw(_text_top_right02._item);
    window.draw(_text_multiplayer._item);
    window.draw(_text_settings._item);
    window.draw(_text_bottom_right._item);
}
