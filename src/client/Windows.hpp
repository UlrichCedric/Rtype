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
#include "Image.hpp"
#include "Text.hpp"
#include "Music.hpp"
#include "Paralax.hpp"
#include "Client.hpp"
#include "Button.hpp"
#include "Ennemy.hpp"
#include "Health.hpp"
#include "Shoot.hpp"
#include "Player.hpp"

namespace Game {
    enum State {
        MENU,
        GAME,
        PAUSE,
        END,
    };

    class Windows {
        public:
            Windows(void);
            void Loop(Client &);
            void Display_menu(void);
            void Display_pause(void);
            void Events(void);
            void Events_game(void);
            void Events_pause(void);
            void handleKeyPressed(sf::Event& event);
            void handleKeyReleased(sf::Event& event);
            void handleMenu(void);
            void handleGame(Client &);
            void handlePause(void);
            void handleEnd(void);
            void init(void);
            ~Windows(void) = default;

        private:
            sf::RenderWindow _window;
            std::string _ip;
            sf::Font font;
            int _fps;
            Image _img;
            Image _background;
            Player _player;
            Music _music;
            Paralax _paralax;
            enum Input _key_pressed;
            enum State _state;
            Menu::Button _button;
            Ennemy _ennemy;
            Text _text;
            int _score;
    };
}
