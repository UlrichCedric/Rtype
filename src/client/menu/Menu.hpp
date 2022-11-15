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
        PAUSE,
        GAME,
        LOSE,
        CLOSE,
        END
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
            void handleEventsDeath(sf::Event &event);
            void handleEventsPause(sf::Event &event);

            void handleMenu(sf::RenderWindow &window, State_menu &state, Client &client);

            //Menu
            void initMenu();
            void displayMenu(sf::RenderWindow &window);

            //Lobby
            void initLobby();
            void displayLobby(sf::RenderWindow &window);

            //Settings
            void initSettings();
            void displaySettings(sf::RenderWindow &window);
            int getFps();
            State_menu getState();
            void setState(State_menu state) { _state = state; }

            //death screen
            void iniDeath();
            void displayDeath(sf::RenderWindow &window);

            void initPause();
            void displayPause(sf::RenderWindow &window);

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
            Game::Text _menu_text_quit;
            Game::Text _menu_text_bottom_right;
            Game::Image _menu_rect_selection;
            enum _selection_possibility_menu {MULTIPLAYER_SELECTION, SETTINGS_SELECTION , QUIT_SELECTION};
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
            Game::Image _edit_icon_game_name;
            sf::RectangleShape _rect_select_create_lobby_modal;
            enum _selection_possibility_create_lobby_modal {GAME_NAME, WRITING_GAME_NAME, VALIDATE_CREATE_LOBBY};
            _selection_possibility_create_lobby_modal _create_lobby_modal_select;
            // Join a lobby
            boost::uuids::uuid get_uuid_of_selected_lobby();

            // Settings
            enum _selection_possibility_settings {MUSIC_VOLUME_TITLE, MUSIC_VOLUME_MODIF, SOUNDS_VOLUME_TITLE, SOUNDS_VOLUME_MODIF, FPS_TITLE, FPS_MODIF};
            _selection_possibility_settings _settings_select;
            Game::Text _settings_title;
            Game::Text _settings_music_volume;
            Game::Text _settings_sonds_volume;
            Game::Text _settings_fps;
            Game::Image _settings_rect_selection;
            sf::RectangleShape _settings_music_volume_bar;
            sf::RectangleShape _settings_music_volume_progression_bar;
            sf::RectangleShape _settings_sounds_volume_bar;
            sf::RectangleShape _settings_sounds_volume_progression_bar;
            std::array<int, 3> _fps;
            size_t _fps_index;

            //death screen
            enum _selection_possibility_death {RETRY, QUIT};
            _selection_possibility_death _death_select;
            Game::Text _death_title;
            Game::Text _death_retry;
            Game::Text _death_quit;
            Game::Image _death_rect_selection;
            std::array<std::string, 4> _death_text;

            //win screen
            enum _selection_possibility_win {RETRY_WIN, QUIT_WIN};
            _selection_possibility_win _win_select;
            Game::Text _win_title;
            Game::Text _win_retry;
            Game::Text _win_quit;
            Game::Image _win_rect_selection;

            //pause screen
            enum _selection_possibility_pause {MUSIC_VOLUME_TITLE_PAUSE, MUSIC_VOLUME_MODIF_PAUSE, SOUNDS_VOLUME_TITLE_PAUSE, SOUNDS_VOLUME_MODIF_PAUSE, FPS_TITLE_PAUSE, FPS_MODIF_PAUSE, RESUME, QUIT_PAUSE};
            _selection_possibility_pause _pause_select; 
            Game::Text _settings_pause_title;
            Game::Text _settings_pause_music_volume;
            Game::Text _settings_pause_sonds_volume;
            Game::Text _settings_pause_fps;
            Game::Text _settings_pause_resume;
            Game::Text _settings_pause_quit;
            sf::RectangleShape _settings_pause_music_volume_bar;
            sf::RectangleShape _settings_pause_music_volume_progression_bar;
            sf::RectangleShape _settings_pause_sounds_volume_bar;
            sf::RectangleShape _settings_pause_sounds_volume_progression_bar;
            Game::Image _settings_pause_rect_selection;
    };  
}

#endif /* !MENU_HPP_ */
