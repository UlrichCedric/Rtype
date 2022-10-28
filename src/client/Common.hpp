/*
** EPITECH PROJECT, 2022
** Common
** File description:
** common data for server and client
*/

#pragma once

#include <iostream>

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp> // <iostream> for uuid

enum Input {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SPACE,
    NONE
};

/**
   *  input: The current input pressed by the user or NONE.
   *  uuid: the uuid of the player
*/

typedef struct Action {
    enum Input input;
    boost::uuids::uuid uuid;
} Action;

/**
   *  coords: pair of coords of the sprite (x, y)
   *  id: the id of the sprite
*/

typedef struct SpriteData {
    std::pair<float, float> coords;
    std::size_t id;
} SpriteData;

/*
    List of sprites that can move:
        - Players
        - Projectiles
        - Ennemies
*/
