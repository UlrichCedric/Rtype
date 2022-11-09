/*
** EPITECH PROJECT, 2022
** Rtype [WSL : Ubuntu]
** File description:
** Events
*/

#include "Menu.hpp"

void Menu::Menu::handleEventsMenu(sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::Up) {
            if (_menu_select == SETTINGS_SELECTION) {
                _navigation_sound.play();
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
                _navigation_sound.play();
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
                _validate_sound.play();
                _state = State_menu::LOBBY;
            }
            else if (_menu_select == SETTINGS_SELECTION) {
                _validate_sound.play();
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
        else if (event.key.code == sf::Keyboard::Return) {
            _state = State_menu::GAME;
        }
        else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
            if (_lobby_select == CREATE_A_LOBBY) {
                _lobby_select = REFRESH_ICON;
                _lobby_rect_selection.setRect(0, 0, 36, 36);
                _lobby_rect_selection.setPos(1018, 153);
                _lobby_refresh_icon.setColor(sf::Color::Black);
                _lobby_create.setFontColor(sf::Color::White);
                _lobby_create.setFontStyle(sf::Text::Regular);
            }
        }
        else if (event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::Left) {
            if (_lobby_select == REFRESH_ICON) {
                _lobby_select = CREATE_A_LOBBY;
                _lobby_rect_selection.setRect(0, 0, 385, 45);
                _lobby_rect_selection.setPos(210, 145);
                _lobby_create.setFontColor(sf::Color::Black);
                _lobby_create.setFontStyle(sf::Text::Bold);
                _lobby_refresh_icon.setColor(sf::Color::White);
            }
        }
        else if (event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::Up) {
            if (_lobby_select == BOX_LIST_LOBBY) {
                switch(index_of_game_lobby_selected) {
                    case (0):
                        _lobby_select = CREATE_A_LOBBY;
                        _lobby_rect_selection.setRect(0, 0, 385, 45);
                        _lobby_rect_selection.setPos(210, 145);
                        _lobby_create.setFontColor(sf::Color::Black);
                        _lobby_create.setFontStyle(sf::Text::Bold);
                        break;
                    case (1):
                        _lobby_box_selection.setPosition(215, 205);
                        index_of_game_lobby_selected = 0;
                        break;
                    case (2):
                        _lobby_box_selection.setPosition(215, 295);
                        index_of_game_lobby_selected = 1;
                        break;
                    case (3):
                        _lobby_box_selection.setPosition(215, 385);
                        index_of_game_lobby_selected = 2;
                        break;
                    case (4): 
                        _lobby_box_selection.setPosition(215, 475);
                        index_of_game_lobby_selected = 3;
                    break;
                    default: break;
                }
            }
        }
        else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
            if (_lobby_select == REFRESH_ICON) {
                _lobby_select = BOX_LIST_LOBBY;
                index_of_game_lobby_selected = 0;
                _lobby_refresh_icon.setColor(sf::Color::White);
            }
            else if (_lobby_select == CREATE_A_LOBBY) {
                _lobby_select = BOX_LIST_LOBBY;
                index_of_game_lobby_selected = 0;
                _lobby_create.setFontColor(sf::Color::White);
                _lobby_create.setFontStyle(sf::Text::Regular);
            }
            else if (_lobby_select == BOX_LIST_LOBBY) {
                switch(index_of_game_lobby_selected) {
                    case (0):
                        _lobby_box_selection.setPosition(215, 295);
                        index_of_game_lobby_selected = 1;
                        break;
                    case (1):
                        _lobby_box_selection.setPosition(215, 385);
                        index_of_game_lobby_selected = 2;
                        break;
                    case (2):
                        _lobby_box_selection.setPosition(215, 475);
                        index_of_game_lobby_selected = 3;
                        break;
                    case (3):
                        _lobby_box_selection.setPosition(215, 565);
                        index_of_game_lobby_selected = 4;
                        break;
                    case (4): break;
                    default: break;
                }
            }
        }
    }
}

void Menu::Menu::handleEventsSettings(sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            if (_settings_select == MUSIC_VOLUME_MODIF) {
                _validate_sound.play();
                _settings_select = MUSIC_VOLUME_TITLE;
                _settings_music_volume.setFontStyle(sf::Text::Bold);
                _settings_music_volume.setFontColor(sf::Color::Black);
                _settings_music_volume_progression_bar.setFillColor(sf::Color(236, 236, 236));
            }
            else if (_settings_select == SOUNDS_VOLUME_MODIF) {
                _validate_sound.play();
                _settings_select = SOUNDS_VOLUME_TITLE;
                _settings_sonds_volume.setFontStyle(sf::Text::Bold);
                _settings_sonds_volume.setFontColor(sf::Color::Black);
                _settings_sounds_volume_progression_bar.setFillColor(sf::Color(236, 236, 236));
            }
            else {
                _validate_sound.play();
                _state = State_menu::MENU;
            }
        }
        else if (event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::Up) {
            if (_settings_select == SOUNDS_VOLUME_TITLE) {
                _navigation_sound.play();
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
                _navigation_sound.play();
                _settings_select = SOUNDS_VOLUME_TITLE;
                _settings_rect_selection.setPos(130, 315);
                _settings_sonds_volume.setFontStyle(sf::Text::Bold);
                _settings_sonds_volume.setFontColor(sf::Color::Black);
                _settings_music_volume.setFontStyle(sf::Text::Regular);
                _settings_music_volume.setFontColor(sf::Color::White);
            }
        }
        else if (event.key.code == sf::Keyboard::Return) {
            if (_settings_select == MUSIC_VOLUME_TITLE) {
                _validate_sound.play();
                _settings_select = MUSIC_VOLUME_MODIF;
                _settings_music_volume.setFontStyle(sf::Text::Regular);
                _settings_music_volume.setFontColor(sf::Color::White);
                _settings_music_volume_progression_bar.setFillColor(sf::Color(128, 128, 128));
            }
            else if (_settings_select == SOUNDS_VOLUME_TITLE) {
                _validate_sound.play();
                _settings_select = SOUNDS_VOLUME_MODIF;
                _settings_sonds_volume.setFontStyle(sf::Text::Regular);
                _settings_sonds_volume.setFontColor(sf::Color::White);
                _settings_sounds_volume_progression_bar.setFillColor(sf::Color(128, 128, 128));
            }
        }
        else if (event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::Left) {
            if (_settings_select == MUSIC_VOLUME_MODIF) {
                if (_music_volume > 0.0f) {
                    _music_volume -= 2.0f;
                    _settings_music_volume_progression_bar.setSize(sf::Vector2f((869 * (_music_volume / 100)), 44));
                    _music.setVolume(_music_volume);
                }
            }
            else if (_settings_select == SOUNDS_VOLUME_MODIF) {
                if (_sounds_volume > 0.0f) {
                    _sounds_volume -= 2.0f;
                    _settings_sounds_volume_progression_bar.setSize(sf::Vector2f((869 * (_sounds_volume / 100)), 44));
                    _navigation_sound.setVolume(_sounds_volume);
                    _validate_sound.setVolume(_sounds_volume);
                }
            }
        }
        else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
            if (_settings_select == MUSIC_VOLUME_MODIF) {
                if (_music_volume < 100.0f) {
                    _music_volume += 2.0f;
                    _settings_music_volume_progression_bar.setSize(sf::Vector2f((869 * (_music_volume / 100)), 44));
                    _music.setVolume(_music_volume);
                }
            }
            else if (_settings_select == SOUNDS_VOLUME_MODIF) {
                if (_sounds_volume < 100.0f) {
                    _sounds_volume += 2.0f;
                    _settings_sounds_volume_progression_bar.setSize(sf::Vector2f((869 * (_sounds_volume / 100)), 44));
                    _navigation_sound.setVolume(_sounds_volume);
                    _validate_sound.setVolume(_sounds_volume);
                }
            }
        }
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
