/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak
** File description:
** Paralax
*/

#pragma once
#include "utils/Image.hpp"
#include "Config.hpp"

namespace Game {
    enum paralax {
        MENU_PARALAX,
        GAME_PARALAX,
    };

    class Paralax {
        public:
            Paralax(){};
            ~Paralax();
            void setSprites(paralax which_paralax);
            void update(paralax which_paralax);
            void draw(sf::RenderWindow &window, paralax which_paralax);
        private:
            Image back;
            Image stars;
            Image planet;
            Image planet2;
            Image stars2;
    };
}

