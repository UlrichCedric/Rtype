/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak
** File description:
** main
*/

#pragma once

#include "Error.hpp"

class ClientError: public Error {
    public:
    ClientError(std::string str = "Client error") { _str = str; }
    const char *what(void) noexcept { return _str.c_str(); }
    ~ClientError() {}
};
