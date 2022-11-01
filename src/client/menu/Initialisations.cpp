/*
** EPITECH PROJECT, 2022
** Rtype [WSL : Ubuntu]
** File description:
** Initialisations
*/

#include "Menu.hpp"

void Menu::Menu::initMenu()
{
    _menu_select = MULTIPLAYER_SELECTION;
    _menu_title.setTexture(Game::Config::ExecutablePath + "assets/menu/sprites/R-TYPE_title.png");
    _menu_title.setPos(15, 430);
    // Load Fonts
    _menu_text_bottom_right = Text("assets/menu/fonts/r-type.ttf");
    _menu_text_multiplayer = Text("assets/menu/fonts/r-type.ttf");
    _menu_text_settings = Text("assets/menu/fonts/r-type.ttf");
    _menu_text_top_right01 = Text("assets/menu/fonts/r-type.ttf");
    _menu_text_top_right02 = Text("assets/menu/fonts/r-type.ttf");
    //_text_top_right01
    _menu_text_top_right01.SetText("BLAST OFF AND STRIKE");
    _menu_text_top_right01.setFontSize(20);
    _menu_text_top_right01.setPos(830, 15);
    //_text_top_right02
    _menu_text_top_right02.SetText("THE EVIL BYDO EMPIRE!");
    _menu_text_top_right02.setFontSize(20);
    _menu_text_top_right02.setPos(830, 45);
    //_text_multiplayer
    _menu_text_multiplayer.SetText("MULTIPLAYER");
    _menu_text_multiplayer.setFontSize(30);
    _menu_text_multiplayer.setFontColor(sf::Color::Black);
    _menu_text_multiplayer.setFontStyle(sf::Text::Bold);
    _menu_text_multiplayer.setPos(920, 180);
    //_text_settings
    _menu_text_settings.SetText("SETTINGS");
    _menu_text_settings.setFontSize(30);
    _menu_text_settings.setPos(995, 270);
    //_text_bottom_right
    _menu_text_bottom_right.SetText("Epitech project 2022");
    _menu_text_bottom_right.setFontSize(20);
    _menu_text_bottom_right.setPos(835, 670);
    //_rect_selection
    _menu_rect_selection.setTexture(Game::Config::ExecutablePath + "assets/menu/sprites/white_rect.jpg");
    _menu_rect_selection.setRect(0, 0, 360, 56);
    _menu_rect_selection.setPos(910, 170);
}

void Menu::Menu::initLobby()
{

}

void Menu::Menu::initSettings()
{
    _settings_select = MUSIC_VOLUME_TITLE;

    //_rect_selection
    _settings_rect_selection.setTexture(Game::Config::ExecutablePath + "assets/menu/sprites/white_rect.jpg");
    _settings_rect_selection.setRect(0, 0, 390, 45);
    _settings_rect_selection.setPos(130, 175);
    //fonts
    _settings_title = Text("assets/menu/fonts/r-type.ttf");
    _settings_music_volume = Text("assets/menu/fonts/r-type.ttf");
    _settings_sonds_volume = Text("assets/menu/fonts/r-type.ttf");
    //_settings_title
    _settings_title.SetText("Settings");
    _settings_title.setFontSize(50);
    _settings_title.setFontStyle(sf::Text::Bold);
    _settings_title.setPos(80, 60);
    //_settings_volume_music
    _settings_music_volume.SetText("Music Volume");
    _settings_music_volume.setFontSize(30);
    _settings_music_volume.setFontColor(sf::Color::Black);
    _settings_music_volume.setFontStyle(sf::Text::Bold);
    _settings_music_volume.setPos(140, 180);
    //_settings_sonds_volume
    _settings_sonds_volume.SetText("Sonds Volume");
    _settings_sonds_volume.setFontSize(30);
    _settings_sonds_volume.setPos(140, 320);

    //music volume bar
    _settings_music_volume_bar.setSize(sf::Vector2f(875, 50));
    _settings_music_volume_bar.setOutlineColor(sf::Color::White);
    _settings_music_volume_bar.setOutlineThickness(2);
    _settings_music_volume_bar.setFillColor(sf::Color::Black);
    _settings_music_volume_bar.setPosition(160, 230);
    _settings_music_volume_progression_bar.setSize(sf::Vector2f(443, 50));
    //sonds volume bar
    _settings_sonds_volume_bar.setSize(sf::Vector2f(875, 50));
    _settings_sonds_volume_bar.setOutlineColor(sf::Color::White);
    _settings_sonds_volume_bar.setOutlineThickness(2);
    _settings_sonds_volume_bar.setFillColor(sf::Color::Black);
    _settings_sonds_volume_bar.setPosition(160, 370);
    _settings_sonds_volume_progression_bar.setSize(sf::Vector2f(120, 50));

}

