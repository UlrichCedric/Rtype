/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak [WSL : Ubuntu-22.04]
** File description:
** Music
*/
#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <exception>
#include <iostream>
#include "../../Errors.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../Config.hpp"


class Sound {
    public:
        Sound() {};
        void setPath(std::string path);
        void play() { _sound.play(); };
        void replay() { _sound.stop(); _sound.play(); };
        void stop() { _sound.stop(); };
        void isRepeatable(bool repeat) { _sound.setLoop(repeat); };
        void setVolume(float volume) { _sound.setVolume(volume); };
        ~Sound() {};
    private:
        sf::Sound _sound;
        sf::SoundBuffer _sound_buffer;
};

