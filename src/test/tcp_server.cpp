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
        tcp_server(boost::asio::io_context &io_context): _timer(io_context), _keep(true),
            _acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1234)),
            _socket(io_context)
        {
            _acceptor.accept(_socket);
            async_read_();
            send_();
        }
        ~tcp_server()
        {
            std::cout << "Shut down the server" << std::endl;
        }
        void read_(void)
        {
            boost::asio::read(_socket, boost::asio::buffer(_recv_buf));
            if (_recv_buf[0].type == LobbyType) {
                for (int i = 0; _recv_buf[0].lobbies[i].size != 0; i++) {
                    std::cout << "Lobby of uuid: " << _recv_buf[0].lobbies[i].uuid << std::endl;
                }
            }
            std::cout << "Read ended" << std::endl;
        }
        void async_read_(void)
        {
            boost::asio::async_read(_socket, boost::asio::buffer(_recv_buf),
                boost::bind(&tcp_server::handle_read_, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
        }
        void handle_read_(boost::system::error_code const& error, size_t bytes_transferred)
        {
            if ((boost::asio::error::eof == error) ||
                (boost::asio::error::connection_reset == error)) {
                std::cout << "player disconnected" << std::endl;
                _keep = false;
            } else {
                std::cout << "data received from client" << std::endl;
                if (_recv_buf[0].type == LobbyType) {
                    for (int i = 0; _recv_buf[0].lobbies[i].size != 0; i++) {
                        std::cout << "Lobby of uuid: " << _recv_buf[0].lobbies[i].uuid << std::endl;
                    }
                }
            }
            async_read_();
        }
        void send_(void)
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
            boost::asio::write(_socket, boost::asio::buffer(send_buf));
            std::cout << "data sent to client" << std::endl;
            if (_keep) {
                _timer.expires_from_now(boost::posix_time::milliseconds(500));
                _timer.async_wait(boost::bind(&tcp_server::send_, this));
            }
        }
    private:
        union { boost::array <Data, 1> _recv_buf; };
        boost::asio::ip::tcp::acceptor _acceptor;
        boost::asio::ip::tcp::socket _socket;
        boost::asio::deadline_timer _timer;
        bool _keep;
};

int main(void)
{
    boost::asio::io_service io_context;
    tcp_server server(io_context);
    io_context.run();
    return 0;
}
