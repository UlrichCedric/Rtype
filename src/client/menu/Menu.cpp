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
    _music_volume = 20.0f;
    _sounds_volume = 20.0f;
    _paralax_menu_background.setSprites(Game::paralax::MENU_PARALAX);
    _music.setPath("assets/menu/sounds/music_menu.ogg");
    _validate_sound.setPath("assets/menu/sounds/validate_sound.wav");
    _navigation_sound.setPath("assets/menu/sounds/navigate_sound.wav");
    _validate_sound.isRepeatable(false);
    _navigation_sound.isRepeatable(false);
    _music.isRepeatable(true);
    _music.setVolume(_music_volume);
    _validate_sound.setVolume(_sounds_volume);
    _navigation_sound.setVolume(_sounds_volume);
    _music.play();
    
    initMenu();
    initLobby();
    initSettings();
}

Menu::Menu::~Menu()
{
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

