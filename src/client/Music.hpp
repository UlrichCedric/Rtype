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
#include "../Errors.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Config.hpp"


namespace Game {
    class Music {
        public:
            Music();
            void play() { _music.play(); };
            void replay() { _music.stop(); _music.play(); };
            void stop() { _music.stop(); };
            void isRepeatable(bool repeat) { _music.setLoop(repeat); };
            void setVolume(float volume) { _music.setVolume(volume); };
            ~Music() {};
        private:
            sf::Music _music;
            std::string path;
    };
}
