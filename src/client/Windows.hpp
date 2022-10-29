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
#include "Config.hpp"
#include "../Errors.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "utils/Image.hpp"
#include "Text.hpp"
#include "Music.hpp"
#include "Paralax.hpp"
#include "Client.hpp"
#include "Common.hpp"
#include "utils/Button.hpp"
#include "Ennemy.hpp"
#include "Health.hpp"
#include "Shoot.hpp"
#include "Player.hpp"
#include "menu/Menu.hpp"

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
            void Loop(/*Client& client*/);
            void Display_menu();
            void Display_pause();
            void Events();
            void Events_game();
            void Events_pause();
            void handleKeyPressed(sf::Event& event);
            void handleKeyReleased(sf::Event& event);
            void handleGame(void);
            void handlePause(void);
            void handleEnd(void);
            void init();
            ~Windows() {};
        private:
            Menu::Menu _menu;
            sf::RenderWindow window;
            std::string _ip;
            sf::Font font;
            int fps;
            Image img;
            Image background;
            Player _player;
            Music _music;
            Paralax paralax;
            enum Input _key_pressed;
            enum State _state;
            Ennemy _ennemy;
            Text _text;
            int _score;
    };
}
