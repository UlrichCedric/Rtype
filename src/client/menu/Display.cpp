/*
** EPITECH PROJECT, 2022
** Rtype [WSL : Ubuntu]
** File description:
** Display
*/

#include "Menu.hpp"

void Menu::Menu::displayMenu(sf::RenderWindow &window)
{
    window.draw(_menu_title.get_sprite());
    window.draw(_menu_rect_selection.get_sprite());
    window.draw(_menu_text_top_right01._item);
    window.draw(_menu_text_top_right02._item);
    window.draw(_menu_text_multiplayer._item);
    window.draw(_menu_text_settings._item);
    window.draw(_menu_text_bottom_right._item);
    window.draw(_menu_text_quit._item);
}

void Menu::Menu::displayLobby(sf::RenderWindow &window)
{
    //display rect selection for create a lobby and refresh list
    if (_lobby_select != BOX_LIST_LOBBY) {
        window.draw(_lobby_rect_selection.get_sprite());
    }
    window.draw(_lobby_title._item);
    window.draw(_lobby_create._item);
    window.draw(_lobby_refresh_icon.get_sprite());
    window.draw(_lobby_box_list);
    _game1_lobby.display(window);
    _game2_lobby.display(window);
    _game3_lobby.display(window);
    _game4_lobby.display(window);
    _game5_lobby.display(window);
    //display rect selection game lobby
    if (_lobby_select != CREATE_A_LOBBY && _lobby_select != REFRESH_ICON && _lobby_select != CREATE_A_LOBBY_MODAL)
        window.draw(_lobby_box_selection);
    if (_lobby_select == CREATE_A_LOBBY_MODAL) {
        window.draw(_create_lobby_modal_alpha);
        window.draw(_create_lobby_modal);
        if (_create_lobby_modal_select == _selection_possibility_create_lobby_modal::GAME_NAME)
            window.draw(_rect_select_create_lobby_modal);
        _game_name_text_box.drawTo(window);
        window.draw(_game_name_title._item);
        _validate_create_lobby_button.draw(window);
        window.draw(_edit_icon_game_name.get_sprite());
    }
}

void Menu::Menu::displaySettings(sf::RenderWindow &window)
{
    //setings title
    window.draw(_settings_title._item);
    //display rect selection
    if (_settings_select != MUSIC_VOLUME_MODIF && _settings_select != SOUNDS_VOLUME_MODIF && _settings_select != FPS_MODIF)
        window.draw(_settings_rect_selection.get_sprite());
    //volume bar
    window.draw(_settings_music_volume._item);
    window.draw(_settings_music_volume_bar);
    window.draw(_settings_music_volume_progression_bar);
    //sounds bar
    window.draw(_settings_sonds_volume._item);
    window.draw(_settings_sounds_volume_bar);
    window.draw(_settings_sounds_volume_progression_bar);
    //fps
    window.draw(_settings_fps._item);
}

void Menu::Menu::displayDeath(sf::RenderWindow &window)
{
    if (_death_select != RETRY && _death_select != QUIT)
        window.draw(_death_rect_selection.get_sprite());
    window.draw(_death_title._item);
    window.draw(_death_rect_selection.get_sprite());
    window.draw(_death_retry._item);
    window.draw(_death_quit._item);
}

void Menu::Menu::displayPause(sf::RenderWindow &window)
{
    window.draw(_settings_pause_title._item);
    //display rect selection
    if (_pause_select != MUSIC_VOLUME_MODIF_PAUSE && _pause_select != SOUNDS_VOLUME_MODIF_PAUSE && _pause_select != FPS_MODIF_PAUSE && _pause_select != RESUME && _pause_select != QUIT_PAUSE)
        window.draw(_settings_pause_rect_selection.get_sprite());
    //volume bar
    window.draw(_settings_pause_music_volume._item);
    window.draw(_settings_pause_music_volume_bar);
    window.draw(_settings_pause_music_volume_progression_bar);
    //sounds bar
    window.draw(_settings_pause_sonds_volume._item);
    window.draw(_settings_pause_sounds_volume_bar);
    window.draw(_settings_pause_sounds_volume_progression_bar);
    //fps
    window.draw(_settings_pause_fps._item);
    window.draw(_settings_pause_resume._item);
    window.draw(_settings_pause_quit._item);
}