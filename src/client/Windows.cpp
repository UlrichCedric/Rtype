/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak [WSL : Ubuntu-22.04]
** File description:
** Windows
*/

#include "Windows.hpp"

namespace Game {
    Windows::Windows()
    {
        playerX = 0;
        playerY = 0;
        inGame = true;
        inPause = false;
        fps = 60;
        img.setTexture(Config::ExecutablePath + "assets/background.jpg");
        background.setTexture(Config::ExecutablePath + "assets/background_menu.jpg");
        player.setTexture(Config::ExecutablePath + "assets/player.png");
        player.setScale(3.0, 3.0);
        player.setPos(100, 100);
        player.setRect(playerX, playerY, 33, 17);
        // _music.isRepeatable(true);
        // _music.play();
        _key_pressed = NONE;
    }

    void Windows::Display()
    {
        window.clear();
        window.draw(img.get_sprite());
        window.display();
    }

    void Windows::Display_menu()
    {
        window.clear();
        window.draw(background.get_sprite());
        window.display();
    }

    void Windows::init()
    {
        try {
            window.create(sf::VideoMode(1280, 920, 32), "R-Type");
            window.setFramerateLimit(fps);
        } catch (std::exception &e) {
            throw WindowCreationError();
        }
        return;
    }

    void Windows::Events()
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    void Windows::handleKeyPressed(sf::Event& event)
    {
        if (_key_pressed != NONE) {
            return;
        }
        switch (event.key.code) {
            case sf::Keyboard::Left:
                _key_pressed = LEFT;
                break;
            case sf::Keyboard::Right:
                _key_pressed = RIGHT;
                break;
            case sf::Keyboard::Up:
                _key_pressed = UP;
                break;
            case sf::Keyboard::Down:
                _key_pressed = DOWN;
                break;
            default: break;
        }
    }

    void Windows::handleKeyReleased(sf::Event& event)
    {
        switch (event.key.code) {
            case sf::Keyboard::Escape:
                inPause = true;
                inGame = false;
                break;
            case sf::Keyboard::Left:
                _key_pressed == LEFT ? _key_pressed = NONE : false;
                break;
            case sf::Keyboard::Right:
                _key_pressed == RIGHT ? _key_pressed = NONE : false;
                break;
            case sf::Keyboard::Up:
                _key_pressed == UP ? _key_pressed = NONE : false;
                break;
            case sf::Keyboard::Down:
                _key_pressed == DOWN ? _key_pressed = NONE : false;
                break;
            default: break;
        }
    }

    void Windows::Events_game()
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            switch (event.type) {
                case sf::Event::KeyPressed:
                    handleKeyPressed(event);
                    break;
                case sf::Event::KeyReleased:
                    handleKeyReleased(event);
                    break;
                default: break;
            }
        }
    }

    void Windows::Events_pause()
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    inGame = true;
                    inPause = false;
                }
            }
        }
    }

    void Windows::Loop(Client &client)
    {
        while (window.isOpen()) {
            client.sendData(_key_pressed);

            boost::array<SpriteData, 16> recv_buf;
            client.receiveData(recv_buf);

            for (int i = 0; recv_buf[i].id != 0; i++) {
                // std::cout << "id: " <<
                //     recv_buf[i].id << "\t-> x: " <<
                //     recv_buf[i].coords.first << "\t y: "<<
                //     recv_buf[i].coords.second << std::endl;

                /*
                    Pour l'instant il n'y a que le sprite du joueur
                */
                playerX = recv_buf[i].coords.first;
                playerY = recv_buf[i].coords.second;
                std::cout << "x: " << playerX << " / y: " << playerY << std::endl;
                player.setPos(playerX, playerY);
            }
            if (!inGame) {
                Events();
                Display_menu();
            } else if (inGame) {
                Events_game();
                window.clear();
                paralax.update();
                paralax.draw(window);
                window.draw(player.get_sprite());
                window.display();
            } else if (inPause) {
                Display_menu();
                Events_pause();
            } else {
                std::cout << "Error" << std::endl;
            }
        }
        _music.stop();
    }
}