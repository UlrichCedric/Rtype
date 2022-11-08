/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak
** File description:
** Health
*/

#include "Health.hpp"

namespace Game {
    Health::Health(sf::Vector2f Barre, float x, float y, int max_life)
    {
        _vieMax = max_life;
        _vieActuelle = max_life;
        _vieManquante = 0;
        _coefficientReducteur = 100 / _vieMax;
        _dimensionCadre = Barre;
        _cadre.setSize(_dimensionCadre);
        _cadre.setFillColor(sf::Color::Red);
        _cadre.setPosition(x, y);
        _barreVariable.setSize(sf::Vector2f(_dimensionCadre.x - 2, _dimensionCadre.y - 2));
        _barreVariable.setFillColor(sf::Color::Green);
        _barreVariable.setPosition(x + 1, y + 1);
    }

    void Health::update(float x, float y, int life)
    {
        _vieActuelle = life;
        _vieManquante = _vieMax - _vieActuelle;
        _barreVariable.setSize(sf::Vector2f((_dimensionCadre.x - 2) - (_vieManquante * _coefficientReducteur), _dimensionCadre.y - 2));
        _cadre.setPosition(x, y);
        _barreVariable.setPosition(x + 1, y + 1);
    }

    void Health::draw(sf::RenderWindow &window)
    {
        window.draw(_cadre);
        window.draw(_barreVariable);
    }
}
