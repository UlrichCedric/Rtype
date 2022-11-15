/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak [WSL : Ubuntu-22.04]
** File description:
** main
*/

#pragma once

#include <exception>
#include <string>

class Error: public std::exception {
    public:
        Error(std::string str = "Error"): _str(str) {}
        const char *what(void) noexcept { return _str.c_str(); }
        ~Error() = default;

    protected:
        std::string _str;
};

