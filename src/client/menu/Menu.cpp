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
    _music.setPath("assets/menu/sounds/music_menu.wav");
    _validate_sound.setPath("assets/menu/sounds/validate_sound.wav");
    _navigation_sound.setPath("assets/menu/sounds/navigate_sound.wav");
    _validate_sound.isRepeatable(false);
    _navigation_sound.isRepeatable(false);
    _music.isRepeatable(true);
    _music.setVolume(_music_volume);
    _validate_sound.setVolume(_sounds_volume);
    _navigation_sound.setVolume(_sounds_volume);
    _music.play();

    // ici on va devoir créer une class pour communiquer en TCP avec le serv. Il faudra aussi avoir une fonction qui demande une liste de lobby existant
    // Les infos concernant les lobby sont : nom, status{open, in game}, nbr de joueurs
    // Ensuite stocker ces infos dans la liste de lobby (côté client)
    initMenu();
    initLobby();
    initSettings();
}

Menu::Menu::~Menu()
{
}

void Menu::Menu::handleMenu(sf::RenderWindow &window, State &state)
{
    this->handleEvents(window);
    window.clear();
    _paralax_menu_background.update(Game::MENU_PARALAX);
    _paralax_menu_background.draw(window, Game::MENU_PARALAX);
    switch (_state) {
        case MENU: displayMenu(window); break;
        case LOBBY: displayLobby(window); break;
        case SETTINGS: displaySettings(window); break;
        case GAME: state = State::GAME; break;
        default: break;
    }
    window.display();
}

void Menu::Menu::fetchLobbyList()
{
    std::vector<_game_lobby>::iterator it = _game_lobby_list.begin();

    for (int i = 0; it != _game_lobby_list.end(); it++, i++) {
        switch (i) {
            case (0): _game1_lobby.initGameLobby(it->status, it->name, it->nb_players); _game1_lobby.setPosition(0); break;
            case (1): _game2_lobby.initGameLobby(it->status, it->name, it->nb_players); _game2_lobby.setPosition(1); break;
            case (2): _game3_lobby.initGameLobby(it->status, it->name, it->nb_players); _game3_lobby.setPosition(2); break;
            case (3): _game4_lobby.initGameLobby(it->status, it->name, it->nb_players); _game4_lobby.setPosition(3); break;
            case (4): _game5_lobby.initGameLobby(it->status, it->name, it->nb_players); _game5_lobby.setPosition(4); break;
            default: break;
        }
    }
}
