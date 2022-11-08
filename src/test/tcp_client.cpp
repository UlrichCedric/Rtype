/*
** EPITECH PROJECT, 2022
** udp_client
** File description:
** test
*/

#include <boost/uuid/uuid_generators.hpp>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "../Common.hpp"

class tcp_client {
    public:
        tcp_client()
        {
            boost::asio::io_service io_service;
            boost::asio::ip::tcp::socket socket(io_service);
            socket.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));
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
            boost::system::error_code error;
            boost::asio::write(socket, boost::asio::buffer(send_buf), error);
            if (!error) {
                std::cout << "Client sent data!" << std::endl;
            } else {
                std::cout << "send failed: " << error.message() << std::endl;
            }
            while (true) {
                boost::asio::read(socket, boost::asio::buffer(_recv_buf), error);
                if (!error) {
                    if (_recv_buf[0].type == LobbyType) {
                        for (int i = 0; _recv_buf[0].lobbies[i].size != 0; i++) {
                            std::cout << "Lobby of uuid: " << _recv_buf[0].lobbies[i].uuid << std::endl;
                        }
                    }
                } else {
                    std::cout << "receive failed: " << error.message() << std::endl;
                    break;
                }
            }
        }
        ~tcp_client() {}
    private:
        union { boost::array <Data, 1> _recv_buf; };
};

int main()
{
    tcp_client client;
    return 0;
}
