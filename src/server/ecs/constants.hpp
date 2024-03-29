#pragma once

#include <iostream>
#include <unordered_map>
#include <functional>
#include <array>

const int comp_nb = 10;

enum components {
    DRAWABLE,
    MOVABLE,
    HEALTH,
    VELOCITY,
    POSITION,
    REPEATABLE,
    SOUND,
    UUID,
    SCALE,
    HITBOX
};

static const std::array<std::pair<std::string, int>, comp_nb + 1> strToInt = {
    std::make_pair<std::string, int>("drawable", DRAWABLE),
    std::make_pair<std::string, int>("movable", MOVABLE),
    std::make_pair<std::string, int>("health", HEALTH),
    std::make_pair<std::string, int>("velocity", VELOCITY),
    std::make_pair<std::string, int>("position", POSITION),
    std::make_pair<std::string, int>("repeatable", REPEATABLE),
    std::make_pair<std::string, int>("sound", SOUND),
    std::make_pair<std::string, int>("uuid", UUID),
    std::make_pair<std::string, int>("scale", SCALE),
    std::make_pair<std::string, int>("hitbox", HITBOX),
    std::make_pair<std::string, int>("NULL", -1)
};

inline bool betw(float a, float b, float c) { return a < b && b < c; }
inline bool betw(int a, int b, int c) { return a < b && b < c; }

