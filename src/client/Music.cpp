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
        path = Config::ExecutablePath + "assets/Main.ogg";
        if (!_music.openFromFile(path))
            std::cout << "Unable to open music file : " << path << std::endl;
        else {
            _music.setLoop(false);
        }
    }
}

