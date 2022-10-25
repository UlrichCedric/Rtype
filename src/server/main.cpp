/*
** EPITECH PROJECT, 2022
** udp_server
** File description:
** boost::asio
*/

#include "Server.hpp"
#include <iostream>

int main(int ac, char **av) {
    std::cout << "____ Server started ____" << std::endl;

    try {
        boost::asio::io_context io_context;
        Server server(io_context);
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}