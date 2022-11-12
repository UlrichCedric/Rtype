/*
** EPITECH PROJECT, 2022
** Rtype [WSL : Ubuntu]
** File description:
** Events
*/

#include "Menu.hpp"

boost::uuids::uuid Menu::Menu::get_uuid_of_selected_lobby()
{
    int i = 0;

    for (auto &_game_lobby : _game_lobby_list) {
        if (index_of_game_lobby_selected == i) {
            return _game_lobby.lobby_uuid;
        }
        i++;
    }
    //TODO renvoyer un uuid null ou quelque chose comme ça pour dire que rien n'a été trouvé
    return boost::uuids::uuid();
}

void Menu::Menu::handleEventsMenu(sf::Event &event, Client &client)
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
            else if (_menu_select == QUIT_SELECTION) {
                _navigation_sound.play();
                _menu_select = SETTINGS_SELECTION;
                _menu_rect_selection.setRect(0, 0, 360, 56);
                _menu_rect_selection.setPos(910, 260);
                _menu_text_settings.setFontStyle(sf::Text::Bold);
                _menu_text_settings.setFontColor(sf::Color::Black);
                _menu_text_quit.setFontStyle(sf::Text::Regular);
                _menu_text_quit.setFontColor(sf::Color::White);
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
            else if (_menu_select == SETTINGS_SELECTION) {
                _navigation_sound.play();
                _menu_select = QUIT_SELECTION;
                _menu_rect_selection.setRect(0, 0, 267, 56);
                _menu_rect_selection.setPos(985, 350);
                _menu_text_quit.setFontStyle(sf::Text::Bold);
                _menu_text_quit.setFontColor(sf::Color::Black);
                _menu_text_settings.setFontStyle(sf::Text::Regular);
                _menu_text_settings.setFontColor(sf::Color::White);
            }
        }
        else if (event.key.code == sf::Keyboard::Return) {
            if (_menu_select == MULTIPLAYER_SELECTION) {
                _validate_sound.play();
                _state = State_menu::LOBBY;
                try {
                    _game_lobby_list = client.getLobbies();
                    fetchLobbyList();
                }
                catch (Error &e) {
                    std::cerr << e.what() << std::endl;
                }
            }
            else if (_menu_select == SETTINGS_SELECTION) {
                _validate_sound.play();
                _state = State_menu::SETTINGS;
            }
            else if (_menu_select == QUIT_SELECTION) {
               _state = State_menu::CLOSE;
            }
        }
    }
}

void Menu::Menu::handleEventsLobby(sf::Event &event, Client &client)
{
    if (event.type == sf::Event::TextEntered) {
        if (_lobby_select == CREATE_A_LOBBY_MODAL && _create_lobby_modal_select == WRITING_GAME_NAME) {
            _game_name_text_box.setSelected(true);
            _game_name_text_box.typedOn(event);
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            if (_lobby_select == CREATE_A_LOBBY_MODAL) {
                _validate_sound.play();
                _lobby_select = CREATE_A_LOBBY;
            } else {
                _validate_sound.play();
                _state = State_menu::MENU;
            }
        }
        else if (event.key.code == sf::Keyboard::Return) {
            if (_lobby_select == CREATE_A_LOBBY_MODAL) {
                if (_create_lobby_modal_select == _selection_possibility_create_lobby_modal::GAME_NAME) {
                    _create_lobby_modal_select = _selection_possibility_create_lobby_modal::WRITING_GAME_NAME;
                    _edit_icon_game_name.setColor(sf::Color::White);
                } else if (_create_lobby_modal_select == _selection_possibility_create_lobby_modal::WRITING_GAME_NAME) {
                    _create_lobby_modal_select = _selection_possibility_create_lobby_modal::GAME_NAME;
                    _edit_icon_game_name.setColor(sf::Color::Black);
                    _game_name_text_box.setSelected(false);
                } else if (_create_lobby_modal_select == _selection_possibility_create_lobby_modal::VALIDATE_CREATE_LOBBY) {
                    try {
                        client.createLobby(_game_name_text_box.getText());
                        _game_lobby_list = client.getLobbies();
                        fetchLobbyList();
                        _create_lobby_modal_select = _selection_possibility_create_lobby_modal::GAME_NAME;
                        _lobby_select = CREATE_A_LOBBY;
                    }
                    catch (Error &e) {
                        std::cout << e.what() << std::endl;
                    }
                }
            } else if (_lobby_select == REFRESH_ICON) {
                _validate_sound.play();
                try {
                    _game_lobby_list = client.getLobbies();
                    fetchLobbyList();
                }
                catch (Error &e) {
                    std::cerr << e.what() << std::endl;
                }
            }
            else if (_lobby_select == CREATE_A_LOBBY) {
                _validate_sound.play();
                _lobby_select = CREATE_A_LOBBY_MODAL;
                _create_lobby_modal_select = _selection_possibility_create_lobby_modal::GAME_NAME;
                _edit_icon_game_name.setColor(sf::Color::Black);
                _game_name_text_box.setSelected(false);
                _game_name_text_box.clearText();
                _validate_create_lobby_button.setColorRect(Button::COLOR_CODE::BLACK, Button::COLOR_CODE::WHITE, 2.0f);
                _validate_create_lobby_button.setFontSize(16);
                _validate_create_lobby_button.setFontColor(sf::Color::White);
                _validate_create_lobby_button.setFontStyle(sf::Text::Bold);
            }
            else if (_lobby_select == BOX_LIST_LOBBY) {
                _validate_sound.play();
                try {
                    client.joinLobby(this->get_uuid_of_selected_lobby());
                    _state = State_menu::GAME;
                } catch (Error &e) {
                    std::cout << e.what() << std::endl;
                }
            }
        }
        else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
            if (_lobby_select == CREATE_A_LOBBY) {
                _navigation_sound.play();
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
                _navigation_sound.play();
                _lobby_select = CREATE_A_LOBBY;
                _lobby_rect_selection.setRect(0, 0, 385, 45);
                _lobby_rect_selection.setPos(210, 145);
                _lobby_create.setFontColor(sf::Color::Black);
                _lobby_create.setFontStyle(sf::Text::Bold);
                _lobby_refresh_icon.setColor(sf::Color::White);
            }
        }
        else if (event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::Up) {
            if (_lobby_select == CREATE_A_LOBBY_MODAL) {
                if (_create_lobby_modal_select == _selection_possibility_create_lobby_modal::VALIDATE_CREATE_LOBBY) {
                    _create_lobby_modal_select = _selection_possibility_create_lobby_modal::GAME_NAME;
                    _edit_icon_game_name.setColor(sf::Color::Black);
                    _validate_create_lobby_button.setColorRect(Button::COLOR_CODE::BLACK, Button::COLOR_CODE::WHITE, 2.0f);
                    _validate_create_lobby_button.setFontSize(16);
                    _validate_create_lobby_button.setFontColor(sf::Color::White);
                    _validate_create_lobby_button.setFontStyle(sf::Text::Bold);
                }
            }
            else if (_lobby_select == BOX_LIST_LOBBY) {
                switch(index_of_game_lobby_selected) {
                    case (0):
                        _lobby_select = CREATE_A_LOBBY;
                        _navigation_sound.play();
                        _lobby_rect_selection.setRect(0, 0, 385, 45);
                        _lobby_rect_selection.setPos(210, 145);
                        _lobby_create.setFontColor(sf::Color::Black);
                        _lobby_create.setFontStyle(sf::Text::Bold);
                        break;
                    case (1):
                        _navigation_sound.play();
                        _lobby_box_selection.setPosition(215, 205);
                        index_of_game_lobby_selected = 0;
                        break;
                    case (2):
                        _navigation_sound.play();
                        _lobby_box_selection.setPosition(215, 295);
                        index_of_game_lobby_selected = 1;
                        break;
                    case (3):
                        _navigation_sound.play();
                        _lobby_box_selection.setPosition(215, 385);
                        index_of_game_lobby_selected = 2;
                        break;
                    case (4): 
                        _navigation_sound.play();
                        _lobby_box_selection.setPosition(215, 475);
                        index_of_game_lobby_selected = 3;
                    break;
                    default: break;
                }
            }
        }
        else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
            if (_lobby_select == CREATE_A_LOBBY_MODAL) {
                if (_create_lobby_modal_select == _selection_possibility_create_lobby_modal::GAME_NAME) {
                    _create_lobby_modal_select = _selection_possibility_create_lobby_modal::VALIDATE_CREATE_LOBBY;
                    _edit_icon_game_name.setColor(sf::Color::White);
                    _validate_create_lobby_button.setColorRect(Button::COLOR_CODE::WHITE, Button::COLOR_CODE::BLACK, 2.0f);
                    _validate_create_lobby_button.setFontSize(16);
                    _validate_create_lobby_button.setFontColor(sf::Color::Black);
                    _validate_create_lobby_button.setFontStyle(sf::Text::Bold);
                }
            }
            else if (_lobby_select == REFRESH_ICON && _game_lobby_list.size() > 0) {
                _lobby_select = BOX_LIST_LOBBY;
                _navigation_sound.play();
                index_of_game_lobby_selected = 0;
                _lobby_refresh_icon.setColor(sf::Color::White);
            }
            else if (_lobby_select == CREATE_A_LOBBY && _game_lobby_list.size() > 0) {
                _lobby_select = BOX_LIST_LOBBY;
                _navigation_sound.play();
                index_of_game_lobby_selected = 0;
                _lobby_create.setFontColor(sf::Color::White);
                _lobby_create.setFontStyle(sf::Text::Regular);
            }
            else if (_lobby_select == BOX_LIST_LOBBY) {
                switch(index_of_game_lobby_selected) {
                    case (0):
                        if (_game_lobby_list.size() > 1) {
                            _navigation_sound.play();
                            _lobby_box_selection.setPosition(215, 295);
                            index_of_game_lobby_selected = 1;
                        } break;
                    case (1):
                        if (_game_lobby_list.size() > 2) {
                            _navigation_sound.play();
                            _lobby_box_selection.setPosition(215, 385);
                            index_of_game_lobby_selected = 2;
                        } break;
                    case (2):
                        if (_game_lobby_list.size() > 3) {
                            _navigation_sound.play();
                            _lobby_box_selection.setPosition(215, 475);
                            index_of_game_lobby_selected = 3;
                        } break;
                    case (3):
                        if (_game_lobby_list.size() > 4) {
                            _navigation_sound.play();
                            _lobby_box_selection.setPosition(215, 565);
                            index_of_game_lobby_selected = 4;
                        } break;
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
            else if (_settings_select == FPS_MODIF) {
                _validate_sound.play();
                _settings_select = FPS_TITLE;
                _settings_fps.setFontStyle(sf::Text::Bold);
                _settings_fps.setFontColor(sf::Color::Black);
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
            else if (_settings_select == FPS_TITLE) {
                _navigation_sound.play();
                _settings_select = SOUNDS_VOLUME_TITLE;
                _settings_rect_selection.setRect(0, 0, 390, 45);
                _settings_rect_selection.setPos(130, 315);
                _settings_sonds_volume.setFontStyle(sf::Text::Bold);
                _settings_sonds_volume.setFontColor(sf::Color::Black);
                _settings_fps.setFontStyle(sf::Text::Regular);
                _settings_fps.setFontColor(sf::Color::White);
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
            if (_settings_select == SOUNDS_VOLUME_TITLE) {
                _navigation_sound.play();
                _settings_select = FPS_TITLE;
                _settings_rect_selection.setRect(0, 0, 400, 45);
                _settings_rect_selection.setPos(130, 445);
                _settings_fps.setFontStyle(sf::Text::Bold);
                _settings_fps.setFontColor(sf::Color::Black);
                _settings_sonds_volume.setFontStyle(sf::Text::Regular);
                _settings_sonds_volume.setFontColor(sf::Color::White);
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
            else if (_settings_select == FPS_TITLE) {
                _validate_sound.play();
                _settings_select = FPS_MODIF;
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
            else if (_settings_select == FPS_MODIF) {
                _fps_index--;
                if (_fps_index < 0)
                    _fps_index = 2;
                _settings_fps.SetText("FPS set to " + std::to_string(_fps[_fps_index]));
                _settings_fps.setFontSize(30);
                _settings_fps.setPos(140, 450);
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
            else if (_settings_select == FPS_MODIF) {
                _fps_index++;
                std::cout << _fps_index << std::endl;
                if (_fps_index > 2)
                    _fps_index = 0;
                _settings_fps.SetText("FPS set to " + std::to_string(_fps[_fps_index]));
                _settings_fps.setFontSize(30);
                _settings_fps.setPos(140, 450);
            }
        }
    }
}

void Menu::Menu::handleEvents(sf::RenderWindow &window, Client &client)
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            client.setCanReceiveData(false);
            window.close();
        }
        switch (_state) {
            case MENU: handleEventsMenu(event, client); break;
            case LOBBY: handleEventsLobby(event, client); break;
            case SETTINGS: handleEventsSettings(event); break;
        default: break;
        }
    }
}
