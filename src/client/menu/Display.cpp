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