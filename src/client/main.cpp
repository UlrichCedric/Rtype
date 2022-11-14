/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-marius.nowak
** File description:
** main
*/

#include "Windows.hpp"

int main(int ac, char **av)
{
    Game::Config::initialize();
    Game::Windows win;
    std::string ip = "127.0.0.1";

    if (ac >= 2) {
        ip = std::string(av[1]);
    }

    try {
        Client client(ip, 10001);
        win.init();
        win.GameLoop(client);
    } catch (ClientError &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
