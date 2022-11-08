/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak
** File description:
** Event
*/

#include "../../server/ecs/Entity.hpp"
#include "Event.hpp"

Game::Event::Event()
{
}

char Game::Event::getInput()
{
    return _input;
}

Game::Event makeEvent(Key input)
{
    switch (input) {
        case Up:
            // move_up();
            break;

        case Down:
            // move_down();
            break;

        case Right:
            // move_right();
            break;

        case Left:
            // move_left();
            break;
    }
    Game::Event event;
    return event;
}

Game::Event::~Event()
{
}
