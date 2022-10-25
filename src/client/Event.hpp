/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak
** File description:
** Event
*/

#pragma once

#include <SFML/Graphics.hpp>

enum Key {
    Up,
    Down,
    Right,
    Left,
    Z,
    S,
    Q,
    D,
    Escape
};

namespace Game {
    class Event {
        public:
            Event();
            char getInput();
            Event makeEvent();
            ~Event();

        protected:
            Key _input;
    };
}