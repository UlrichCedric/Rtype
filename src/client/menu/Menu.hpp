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
            void handleEvents(sf::RenderWindow &window);
            void handleMenu(sf::RenderWindow &window);
            void displayMenu(sf::RenderWindow &window);
        private:
            State_menu _state;
            Button _startButton;
            Image background;

            // Menu
            Image _title;
            Text _text_top_right01;
            Text _text_top_right02;
            Text _text_multiplayer;
            Text _text_settings;
            Text _text_bottom_right;
            Image _rect_selection;
            std::size_t _selection;
    };
}

#endif /* !MENU_HPP_ */
