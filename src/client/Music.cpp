/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak [WSL : Ubuntu-22.04]
** File description:
** Music
*/

#include "Music.hpp"

namespace Game {

    Music::Music()
    {
    }

    void Music::setPath(std::string path)
    {
        _path = Config::ExecutablePath + path;
        if (!_music.openFromFile(_path))
            std::cout << "Unable to open music file : " << _path << std::endl;
        else {
            _music.setLoop(false);
        }
    }
}

