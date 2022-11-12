/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak [WSL : Ubuntu-22.04]
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
    class Windows {
        public:
            Windows();
            ~Windows() = default;
            // void Events();
            void GameLoop(Client &client);
            void init();

        private:
            sf::RenderWindow _window;
            std::string _ip;
            sf::Font font;
            int _fps;
            enum State _state;
            
            //Menu
            Menu::Menu _menu;
            //InGame
            InGame _in_game;
    };
}