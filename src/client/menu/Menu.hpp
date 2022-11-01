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
#include "../Config.hpp"
#include "../Music.hpp"
#include "../Paralax.hpp"


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
            void handleEvents(sf::RenderWindow &window);
            void handleEventsMenu(sf::Event &event);
            void handleEventsLobby(sf::Event &event);
            void handleEventsSettings(sf::Event &event);

            void handleMenu(sf::RenderWindow &window);

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
            Game::Music _music;

            //stars parallax
            Game::Paralax _paralax_menu_background;

            // Menu
            Image _menu_title;
            Text _menu_text_top_right01;
            Text _menu_text_top_right02;
            Text _menu_text_multiplayer;
            Text _menu_text_settings;
            Text _menu_text_bottom_right;
            Image _menu_rect_selection;
            enum _selection_possibility_menu {MULTIPLAYER_SELECTION, SETTINGS_SELECTION};
            _selection_possibility_menu _menu_select;

            // Lobby

            // Settings
            enum _selection_possibility_settings {MUSIC_VOLUME_TITLE, MUSIC_VOLUME_MODIF, SONDS_VOLUME_TITLE, SOUNDS_VOLUME_MODIF};
            _selection_possibility_settings _settings_select;
            Text _settings_title;
            Text _settings_music_volume;
            Text _settings_sonds_volume;
            Image _settings_rect_selection;
            sf::RectangleShape _settings_music_volume_bar;
            sf::RectangleShape _settings_music_volume_progression_bar;
            sf::RectangleShape _settings_sonds_volume_bar;
            sf::RectangleShape _settings_sonds_volume_progression_bar;

    };
}

#endif /* !MENU_HPP_ */
