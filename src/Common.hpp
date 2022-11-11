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
    std::pair<float, float> rectSize;

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
        e1.rectSize == e2.rectSize
    );
}

enum Status {
    OPEN,
    CLOSE
};

typedef struct Lobby {
    boost::uuids::uuid player_uuid;
    bool create;
    bool join;
    std::string name;
    std::size_t nb_players;
    std::size_t size;
    boost::uuids::uuid lobby_uuid;
    enum Status status;
} Lobby;

enum Type {
    INITSPRITEDATATYPE,
    SPRITEDATATYPE,
    LOBBYTYPE,
    LOOSE
};

struct Data {
    enum Type type;
    boost::array<SpriteData, 16> spriteDatas;
    boost::array<InitSpriteData, 16> initSpriteDatas;
    boost::array<Lobby, 16> lobbies;
};


struct Wave {
    int index;
    std::string texture_path;
    int ennemy_number;
};