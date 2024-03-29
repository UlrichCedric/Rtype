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
#include <boost/uuid/uuid_generators.hpp>

enum State {
    MENU,
    GAME,
    PAUSE,
    LOSE,
    WIN,
    END,
};

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
struct SpriteData {
    std::size_t id;
    std::pair<float, float> coords;
    int health;
};
/**
   *  coords: pair of coords of the sprite (x, y)
   *  id: the id of the sprite
*/

/**
 * @brief Struct to init a sprite
 *
 */
struct InitSpriteData {
    /**
     * @brief id of the sprite
     *
     */
    std::size_t id;

    /**
     * @brief Path of the texture
     *
     */
    char path[128];

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

    /**
     * @brief Health of the entity
     *
     */
    int health;
};

inline auto operator==(const InitSpriteData &e1, const InitSpriteData &e2) -> bool
{
    return (
        e1.id == e2.id &&
        e1.path == e2.path &&
        e1.coords == e2.coords &&
        e1.scale == e2.scale &&
        e1.maxSize == e2.maxSize
    );
}

enum Status {
    OPEN,
    CLOSE
};

enum Response {
    FORBIDDEN,
    OK
};

typedef struct Lobby {
    boost::uuids::uuid player_uuid;
    bool askForLobbies;
    bool create;
    bool join;
    std::array<char, 64> name;
    std::size_t nb_players;
    std::size_t size;
    boost::uuids::uuid lobby_uuid;
    enum Status status;
} Lobby;

enum Type {
    InitSpriteDataType,
    SpriteDataType,
    LobbyType,
    Loose
};

struct Data {
    enum Type type;
    boost::array<SpriteData, 16> spriteDatas;
    boost::array<InitSpriteData, 16> initSpriteDatas;
    boost::array<Lobby, 16> lobbies;
};