/*
** EPITECH PROJECT, 2022
** udp_server
** File description:
** boost::asio
*/

#include "Server.hpp"

int main(void) {
    try {
        boost::asio::io_context io_context;
        Server server(io_context);
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
