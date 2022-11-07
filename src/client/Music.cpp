/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak [WSL : Ubuntu-22.04]
** File description:
** Music
*/

#include "Music.hpp"

namespace Game {

    void Music::setPath(std::string path)
    {
        std::string path_tmp = Config::ExecutablePath + path;
        if (!_music.openFromFile(path_tmp))
            std::cout << "Unable to open music file : " << path_tmp << std::endl;
        else {
            _music.setLoop(false);
        }
    }
}

