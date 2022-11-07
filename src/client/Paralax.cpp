/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak
** File description:
** Paralax
*/

#include "Paralax.hpp"

namespace Game {

    void Paralax::setSprites(paralax which_paralax)
    {
        if (which_paralax == GAME_PARALAX) {
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
        } else if (which_paralax == MENU_PARALAX) {
            stars.setTexture(Config::ExecutablePath + "assets/menu/sprites/paralax_menu.jpg");
            stars.setPos(0.0, 0.0);
        }
    }


    void Paralax::draw(sf::RenderWindow &window, paralax which_paralax)
    {
        if (which_paralax == GAME_PARALAX) {
            window.draw(back.get_sprite());
            window.draw(planet.get_sprite());
            window.draw(planet2.get_sprite());
            window.draw(stars.get_sprite());
            window.draw(stars2.get_sprite());
        } else if (which_paralax == MENU_PARALAX) {
            window.draw(stars.get_sprite());
        }
    }
        
    void Paralax::update(paralax which_paralax)
    {
        if (which_paralax == GAME_PARALAX) {
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
        else if (which_paralax == MENU_PARALAX) {
            stars.setPos(stars.getPos().x - 4, stars.getPos().y - 2.25);
            if (stars.getPos().y < -720)
                stars.setPos(0.0, 0.0);
        }
    }

    Paralax::~Paralax()
    {
    }
}
