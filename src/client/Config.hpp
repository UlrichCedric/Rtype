/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak
** File description:
** Config
*/

#pragma once
#include <stdexcept>
#include <iostream>
#include <thread>
#include <locale>
#include <codecvt>

#define WIN32_LEAN_AND_MEAN
#ifdef _WIN32
    #include <windows.h>
#else
    # include <unistd.h>
    # include <linux/limits.h>
#endif
#include <string>

namespace Game {
    namespace Config {
            extern std::string  ExecutablePath;
            void initialize();
    };
}
