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
    _paralax_menu_background.setSprites(Game::paralax::MENU_PARALAX);
    _music.setPath("assets/menu/songs/music_menu.ogg");
    _music.isRepeatable(true);
    _music.setVolume(20);
    _music.play();
    
    initMenu();
    initLobby();
    initSettings();
}

Menu::Menu::~Menu()
{
}

void Menu::Menu::handleEventsMenu(sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::Up) {
            if (_menu_select == SETTINGS_SELECTION) {
                _menu_select = MULTIPLAYER_SELECTION;
                _menu_rect_selection.setRect(0, 0, 360, 56);
                _menu_rect_selection.setPos(910, 170);
                _menu_text_multiplayer.setFontStyle(sf::Text::Bold);
                _menu_text_multiplayer.setFontColor(sf::Color::Black);
                _menu_text_settings.setFontStyle(sf::Text::Regular);
                _menu_text_settings.setFontColor(sf::Color::White);
            }
        }
        else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
            if (_menu_select == MULTIPLAYER_SELECTION) {
                _menu_select = SETTINGS_SELECTION;
                _menu_rect_selection.setRect(0, 0, 267, 56);
                _menu_rect_selection.setPos(985, 260);
                _menu_text_settings.setFontStyle(sf::Text::Bold);
                _menu_text_settings.setFontColor(sf::Color::Black);
                _menu_text_multiplayer.setFontStyle(sf::Text::Regular);
                _menu_text_multiplayer.setFontColor(sf::Color::White);
            }
        }
        else if (event.key.code == sf::Keyboard::Return) {
            if (_menu_select == MULTIPLAYER_SELECTION) {
                _state = State_menu::LOBBY;
            }
            else if (_menu_select == SETTINGS_SELECTION) {
                _state = State_menu::SETTINGS;
            }
        }
    }
}

void Menu::Menu::handleEventsLobby(sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            _state = State_menu::MENU;
        }
    }
}

void Menu::Menu::handleEventsSettings(sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            _state = State_menu::MENU;
        }
        else if (event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::Up) {
            if (_settings_select == SONDS_VOLUME_TITLE) {
                _settings_select = MUSIC_VOLUME_TITLE;
                _settings_rect_selection.setPos(130, 175);
                _settings_music_volume.setFontStyle(sf::Text::Bold);
                _settings_music_volume.setFontColor(sf::Color::Black);
                _settings_sonds_volume.setFontStyle(sf::Text::Regular);
                _settings_sonds_volume.setFontColor(sf::Color::White);
            }
        }
        else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
            if (_settings_select == MUSIC_VOLUME_TITLE) {
                _settings_select = SONDS_VOLUME_TITLE;
                _settings_rect_selection.setPos(130, 315);
                _settings_sonds_volume.setFontStyle(sf::Text::Bold);
                _settings_sonds_volume.setFontColor(sf::Color::Black);
                _settings_music_volume.setFontStyle(sf::Text::Regular);
                _settings_music_volume.setFontColor(sf::Color::White);
            }
        }
        // else if (event.key.code == sf::Keyboard::Return) {
        //     if (_menu_select == MULTIPLAYER_SELECTION) {
        //         _state = State_menu::LOBBY;
        //     }
        //     else if (_menu_select == SETTINGS_SELECTION) {
        //         _state = State_menu::SETTINGS;
        //     }
        // }
    }
}

void Menu::Menu::handleEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        switch (_state) {
            case MENU: handleEventsMenu(event); break;
            case LOBBY: handleEventsLobby(event); break;
            case SETTINGS: handleEventsSettings(event); break;
        default: break;
        }
    }
}

void Menu::Menu::handleMenu(sf::RenderWindow &window)
{
    this->handleEvents(window);
    window.clear();
    _paralax_menu_background.update(Game::MENU_PARALAX);
    _paralax_menu_background.draw(window, Game::MENU_PARALAX);
    switch (_state) {
        case MENU: displayMenu(window); break;
        case LOBBY: displayLobby(window); break;
        case SETTINGS: displaySettings(window); break;
        case GAME: break;
        default: break;
    }
    window.display();
}

void Menu::Menu::displayMenu(sf::RenderWindow &window)
{
    window.draw(_menu_title.get_sprite());
    window.draw(_menu_rect_selection.get_sprite());
    window.draw(_menu_text_top_right01._item);
    window.draw(_menu_text_top_right02._item);
    window.draw(_menu_text_multiplayer._item);
    window.draw(_menu_text_settings._item);
    window.draw(_menu_text_bottom_right._item);
}

void Menu::Menu::displayLobby(sf::RenderWindow &window)
{

}

void Menu::Menu::displaySettings(sf::RenderWindow &window)
{
    //setings title
    window.draw(_settings_title._item);
    //display rect selection
    window.draw(_settings_rect_selection.get_sprite());
    //volume bar
    window.draw(_settings_music_volume._item);
    window.draw(_settings_music_volume_bar);
    //sounds bar
    window.draw(_settings_sonds_volume._item);
    window.draw(_settings_sonds_volume_bar);
}
