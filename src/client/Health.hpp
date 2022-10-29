/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak
** File description:
** Health
*/

#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <exception>
#include <iostream>
#include "../Errors.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Config.hpp"
#include "utils/Image.hpp"

namespace Game {
    class Health {
        public:
            Health() {};
            Health(sf::Vector2f Dimension_barre, float x, float y, int max_life);
            void update(float x, float y, int life);
            void draw(sf::RenderWindow &window);
            int getHealth() {return _vieActuelle;};
            ~Health() {};
            sf::RectangleShape _cadre;
            sf::RectangleShape _barreVariable;
            int _vieMax;
            int _vieActuelle;
            int _vieManquante;
            float _coefficientReducteur; //Va servir à se ramener à 100 pour la taille de la barreVie
            sf::Vector2f _dimensionCadre;
    };
};
