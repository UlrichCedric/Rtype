/*
** EPITECH PROJECT, 2022
** Rtype [WSL : Ubuntu]
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include "../utils/Image.hpp"
#include "../utils/Button.hpp"
#include "../utils/Text.hpp"
#include "../utils/Sound.hpp"
#include "../utils/Config.hpp"
#include "../utils/Music.hpp"
#include "../utils/Paralax.hpp"
#include "GameLobby.hpp"
#include "../../Common.hpp"
#include "../game/Client.hpp"
#include "../utils/TextBox.hpp"

namespace Menu {
    enum State_menu {
        MENU,
        LOBBY,
        SETTINGS,
        GAME,
    };

    class Menu {
        public:
            Menu();
            ~Menu();
            //Events
            void handleEvents(sf::RenderWindow &window, Client &client);
            void handleEventsMenu(sf::Event &event, Client &client);
            void handleEventsLobby(sf::Event &event, Client &client);
            void handleEventsSettings(sf::Event &event);

            void handleMenu(sf::RenderWindow &window, State &state, Client &client);

            //Menu
            void initMenu();
            void displayMenu(sf::RenderWindow &window);

            //Lobby
            void initLobby();
            void displayLobby(sf::RenderWindow &window);

            //Settings
            void initSettings();
            void displaySettings(sf::RenderWindow &window);

        private:
            State_menu _state;
            Sound _music;
            Sound _validate_sound;
            Sound _navigation_sound;
            float _music_volume;
            float _sounds_volume;

            //stars parallax
            Game::Paralax _paralax_menu_background;

            // Menu
            Game::Image _menu_title;
            Game::Text _menu_text_top_right01;
            Game::Text _menu_text_top_right02;
            Game::Text _menu_text_multiplayer;
            Game::Text _menu_text_settings;
            Game::Text _menu_text_bottom_right;
            Game::Image _menu_rect_selection;
            enum _selection_possibility_menu {MULTIPLAYER_SELECTION, SETTINGS_SELECTION};
            _selection_possibility_menu _menu_select;

            // Lobby
            enum _selection_possibility_lobby {CREATE_A_LOBBY, REFRESH_ICON, BOX_LIST_LOBBY, CREATE_A_LOBBY_MODAL};
            _selection_possibility_lobby _lobby_select;
            Game::Text _lobby_title;
            Game::Text _lobby_create;
            Game::Image _lobby_refresh_icon;
            sf::RectangleShape _lobby_box_list;
            sf::RectangleShape _lobby_box_selection;
            Game::Image _lobby_rect_selection;
            std::size_t index_of_game_lobby_selected;
            GameLobby _game1_lobby;
            GameLobby _game2_lobby;
            GameLobby _game3_lobby;
            GameLobby _game4_lobby;
            GameLobby _game5_lobby;
            struct _game_lobby {
                std::string name;
                std::string status;
                std::size_t nb_players;
            };
            void fetchLobbyList();
            std::vector<Lobby> _game_lobby_list;
            // Create a lobby
            sf::RectangleShape _create_lobby_modal_alpha;
            sf::RectangleShape _create_lobby_modal;
            TextBox _game_name_text_box;
            Game::Text _game_name_title;
            Button _validate_create_lobby_button;
            // Join a lobby
            boost::uuids::uuid get_uuid_of_selected_lobby();

            // Settings
            enum _selection_possibility_settings {MUSIC_VOLUME_TITLE, MUSIC_VOLUME_MODIF, SOUNDS_VOLUME_TITLE, SOUNDS_VOLUME_MODIF};
            _selection_possibility_settings _settings_select;
            Game::Text _settings_title;
            Game::Text _settings_music_volume;
            Game::Text _settings_sonds_volume;
            Game::Image _settings_rect_selection;
            sf::RectangleShape _settings_music_volume_bar;
            sf::RectangleShape _settings_music_volume_progression_bar;
            sf::RectangleShape _settings_sounds_volume_bar;
            sf::RectangleShape _settings_sounds_volume_progression_bar;

    };
}

#endif /* !MENU_HPP_ */
