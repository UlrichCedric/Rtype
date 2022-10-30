/*
** EPITECH PROJECT, 2022
** Common
** File description:
** common data for server and client
*/

#pragma once

#include <iostream>

#include <boost/any.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
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

/*
    List of sprites that can move:
        - Players
        - Projectiles
        - Ennemies
*/

/**
 * @brief Struct to update a sprite
 *
 */
typedef struct SpriteData_s {
    std::pair<float, float> coords;
    std::size_t id;
} SpriteData;
/**
   *  coords: pair of coords of the sprite (x, y)
   *  id: the id of the sprite
*/

/**
 * @brief Struct to init a sprite
 *
 */
typedef struct InitSpriteData_s {
    /**
     * @brief id of the sprite
     *
     */
    std::size_t id;

    /**
     * @brief Path of the texture
     *
     */
    std::string path;

    /**
     * @brief Spawn coordinates
     *
     */
    std::pair<float, float> coords;

    /**
     * @brief Scale of the sprite
     *
     */
    std::pair<float, float> scale;

    /**
     * @brief Max size of the rect
     *
     */
    std::pair<float, float> maxSize;
} InitSpriteData;

inline bool operator==(const InitSpriteData& e1, const InitSpriteData& e2)
{
    return (
        e1.id == e2.id &&
        e1.path == e2.path &&
        e1.coords == e2.coords &&
        e1.scale == e2.scale &&
        e1.maxSize == e2.maxSize
    );
}

enum Type {
    InitSpriteDataType,
    SpriteDataType,
};

typedef struct Data {
    enum Type type;
    boost::array<boost::any, 16> array;
} Data;
