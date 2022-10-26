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

/**
 * @brief Input events
 *
 */
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
 * @brief Struct to update a sprite
 *
 */
typedef struct SpriteData {
    size_t id;
    std::pair<float, float> coords;
} SpriteData;

/**
 * @brief Struct to init a sprite
 *
 */
typedef struct InitSpriteData_s {
    /**
     * @brief id of the sprite
     *
     */
    size_t id;

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