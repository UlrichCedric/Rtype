/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak [WSL : Ubuntu-22.04]
** File description:
** Sound
*/

#include "Sound.hpp"

void Sound::setPath(std::string path)
    {
        std::string path_tmp = Game::Config::ExecutablePath + path;
        if (!_sound_buffer.loadFromFile(path_tmp))
            std::cout << "Unable to open music file : " << path_tmp << std::endl;
        _sound.setBuffer(_sound_buffer);
        _sound.setLoop(false);
    }