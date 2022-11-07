/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak
** File description:
** Paralax
*/

#include "Paralax.hpp"

namespace Game {
    Paralax::Paralax()
    {
        back.setTexture(Config::ExecutablePath + "assets/paralax/back.png");
        back.setPos(0.0, 0.0);
        back.setScale(5.0, 6.0);
        stars.setTexture(Config::ExecutablePath + "assets/paralax/stars.png");
        stars.setPos(0.0, 0.0);
        stars.setScale(5.0, 6.0);
        planet.setTexture(Config::ExecutablePath + "assets/paralax/planet.png");
        planet.setPos(10.0, 10.0);
        planet.setScale(3.0, 4.0);
        planet2.setTexture(Config::ExecutablePath + "assets/paralax/planet.png");
        planet2.setPos(10.0, 500.0);
        planet2.setScale(3.0, 4.0);
        stars2.setTexture(Config::ExecutablePath + "assets/paralax/stars.png");
        stars2.setPos(0.0, 250.0);
        stars2.setScale(5.0, 6.0);
    }

    void Paralax::draw(sf::RenderWindow &window)
    {
        window.draw(back.get_sprite());
        window.draw(planet.get_sprite());
        window.draw(planet2.get_sprite());
        window.draw(stars.get_sprite());
        window.draw(stars2.get_sprite());
    }
    void Paralax::update()
    {
        stars.setPos(stars.getPos().x - 3, stars.getPos().y);
        if (stars.getPos().x < -1400)
            stars.setPos(1280, stars.getPos().y);
        planet.setPos(planet.getPos().x - 2, planet.getPos().y);
        if (planet.getPos().x < -400)
            planet.setPos(1280, planet.getPos().y);
        stars2.setPos(stars2.getPos().x - 4, stars2.getPos().y);
        if (stars2.getPos().x < -1400)
            stars2.setPos(1280, stars2.getPos().y);
        planet2.setPos(planet2.getPos().x - 1, planet2.getPos().y);
        if (planet2.getPos().x < -400)
            planet2.setPos(1280, planet2.getPos().y);
    }

    Paralax::~Paralax()
    {
    }
}
