/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak
** File description:
** main
*/

#include "Windows.hpp"

int main(void)
{
    Game::Config::initialize();
    Game::Windows win;

    try {
        Client client("127.0.0.1", 10001);
        win.init();
        win.Loop(client);
    } catch (ClientError &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
