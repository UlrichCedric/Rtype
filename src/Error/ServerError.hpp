/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak
** File description:
** main
*/

#pragma once

#include "Error.hpp"

class ServerError: public Error {
    public:
    ServerError(std::string str = "Client error") { _str = str; }
    const char *what(void) noexcept { return _str.c_str(); }
    ~ServerError() {}
};

