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
        _game_name_text_box.drawTo(window);
    }
}

void Menu::Menu::displaySettings(sf::RenderWindow &window)
{
    //setings title
    window.draw(_settings_title._item);
    //display rect selection
    if (_settings_select != MUSIC_VOLUME_MODIF && _settings_select != SOUNDS_VOLUME_MODIF)
        window.draw(_settings_rect_selection.get_sprite());
    //volume bar
    window.draw(_settings_music_volume._item);
    window.draw(_settings_music_volume_bar);
    window.draw(_settings_music_volume_progression_bar);
    //sounds bar
    window.draw(_settings_sonds_volume._item);
    window.draw(_settings_sounds_volume_bar);
    window.draw(_settings_sounds_volume_progression_bar);
}