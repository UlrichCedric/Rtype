/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak
** File description:
** Config
*/

#include "Config.hpp"

namespace Game {
    namespace Config {
        std::string	  ExecutablePath(".");
    };
};

void Game::Config::initialize()
    {
        #ifdef _WIN32
        ::HMODULE handle;
        ::WCHAR   path[MAX_PATH + 1] = { 0 };

        // This error should never happen...
        handle = ::GetModuleHandle(nullptr);
        if (handle == nullptr)
            throw std::runtime_error((std::string(__FILE__) + ": l." + std::to_string(__LINE__)).c_str());
        ::GetModuleFileNameW(handle, path, MAX_PATH);
        Game::Config::ExecutablePath = std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(std::wstring(path).substr(0, std::wstring(path).find_last_of('\\') + 1));
        if (::GetFileAttributesW(path) == INVALID_FILE_ATTRIBUTES)
            puts("invalid path");


#else
            char  path[PATH_MAX + 1] = { 0 };

            // Find executable path from /proc/self/exe
            if (::readlink("/proc/self/exe", path, sizeof(path) - 1) == -1) {
                throw std::runtime_error((std::string(__FILE__) + ": l." + std::to_string(__LINE__)).c_str());
            }

            Game::Config::ExecutablePath = std::string(path).substr(0, std::string(path).find_last_of('/') + 1);
        #endif

}
