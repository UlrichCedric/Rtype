/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak [WSL : Ubuntu-22.04]
** File description:
** Windows
*/

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <exception>
#include <iostream>
#include "utils/Config.hpp"
#include "../Errors.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "utils/Image.hpp"
#include "utils/Text.hpp"
#include "utils/Music.hpp"
#include "utils/Paralax.hpp"
#include "game/Client.hpp"
#include "utils/Button.hpp"
#include "game/Ennemy.hpp"
#include "game/Health.hpp"
#include "game/Shoot.hpp"
#include "game/Player.hpp"
#include "menu/Menu.hpp"
#include "game/InGame.hpp"

namespace Game {
    enum State {
        MENU,
        GAME,
        PAUSE,
        END,
    };

    class Windows {
        public:
            Windows();
            void GameLoop();
            void Display_menu();
            void Display_pause();
            void Events();
            void Events_game();
            void Events_pause();
            void handleKeyPressed(sf::Event& event);
            void handleKeyReleased(sf::Event& event);
            void handleMenu(void);
            void handleGame();
            void handlePause(void);
            void handleEnd(void);
            void init();
            ~Windows() = default;

        private:
            sf::RenderWindow _window;
            std::string _ip;
            sf::Font font;
            int fps;
            Image img;
            Image background;
            Player _player;
            // Music _music;
            Paralax paralax;
            enum Input _key_pressed;
            enum State _state;
            Menu::Button _button;
            Ennemy _ennemy;
            Text _text;
            int _score;
            //Menu
            Menu::Menu _menu;
            //InGame
            InGame _game;
    };
}
