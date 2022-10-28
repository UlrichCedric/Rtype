/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak [WSL : Ubuntu-22.04]
** File description:
** Windows
*/

#pragma once

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
#include "Common.hpp"
#include "../server/ecs/Factory.hpp"
#include "../server/ecs/Systems/HealthSystem.hpp"
#include "../server/ecs/Systems/DrawSystem.hpp"

namespace Game {
    class Windows {
        public:
            Windows();
            void Loop(Client& client);
            void Display();
            void Display_menu();
            void Events();
            void Events_game();
            void Events_pause();
            void handleKeyPressed(sf::Event& event);
            void handleKeyReleased(sf::Event& event);
            void handleMenu(void);
            void handleGame(void);
            void handlePause(void);
            void handleEnd(void);
            void init();
            ~Windows() {};
        private:
            sf::RenderWindow window;
            bool inGame;
            bool isIp;
            bool inPause;
            std::string _ip;
            sf::Font font;
            int fps;
            Image img;
            Image background;
            Image player;
            Music _music;
            Paralax paralax;
            float playerX;
            float playerY;
            enum Input _key_pressed;
            std::unordered_map<std::size_t, Image> _sprites;
    };
}
