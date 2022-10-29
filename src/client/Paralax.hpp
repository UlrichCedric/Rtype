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
    class Paralax {
        public:
            Paralax();
            ~Paralax();
            void update();
            void draw(sf::RenderWindow &window);
        private:
            Image back;
            Image stars;
            Image planet;
            Image planet2;
            Image stars2;
    };
}

