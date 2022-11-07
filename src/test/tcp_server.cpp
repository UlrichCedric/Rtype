/*
** EPITECH PROJECT, 2022
** tcp_server
** File description:
** test
*/

#include <boost/uuid/uuid_generators.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include "../Common.hpp"

class tcp_server {
    public:
        tcp_server()
        {
            boost::asio::io_service io_service;
            boost::asio::ip::tcp::acceptor acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1234));
            boost::asio::ip::tcp::socket socket_(io_service);
            acceptor_.accept(socket_);
            read_(socket_);
            send_(socket_);
            std::cout << "Server sent Data to Client!" << std::endl;
        }
        ~tcp_server() {}
        void read_(boost::asio::ip::tcp::socket& socket)
        {
            boost::asio::read(socket, boost::asio::buffer(_recv_buf));
            if (_recv_buf[0].type == LobbyType) {
                for (int i = 0; _recv_buf[0].lobbies[i].size != 0; i++) {
                    std::cout << "Lobby of uuid: " << _recv_buf[0].lobbies[i].uuid << std::endl;
                }
            }
            std::cout << "Read ended" << std::endl;
        }
        void send_(boost::asio::ip::tcp::socket& socket)
        {
            Lobby lobby1 = {true, true, "lobby1", 2, 4, boost::uuids::random_generator()(), OPEN};
            Lobby lobby2 = {true, true, "lobby2", 2, 4, boost::uuids::random_generator()(), OPEN};
            Lobby lobby3 = {true, true, "lobby3", 2, 4, boost::uuids::random_generator()(), OPEN};
            Lobby endArray = {false, false, "", 0, 0, boost::uuids::random_generator()(), CLOSE};
            boost::array<Lobby, 16> array_buf;
            array_buf[0] = lobby1;
            array_buf[1] = lobby2;
            array_buf[2] = lobby3;
            array_buf[3] = endArray;
            Data data = {LobbyType, {}, {}, array_buf};
            boost::array<Data, 1> send_buf = {data};
            boost::asio::write(socket, boost::asio::buffer(send_buf));
        }
    private:
        union { boost::array <Data, 1> _recv_buf; };
};

int main(void)
{
    tcp_server server;
    return 0;
}
