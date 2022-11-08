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
#include <utility>
#include <memory>
#include <list>
#include "../Common.hpp"

class tcp_server {
    public:
        tcp_server(boost::asio::io_context &io_context): _timer(io_context),
            _acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1234))
        {
            accept_clients();
            send_();
        }

        ~tcp_server()
        {
            std::cout << "Shut down the server" << std::endl;
        }

        void accept_clients(void)
        {
            _acceptor.async_accept(
                [this] (std::error_code ec, boost::asio::ip::tcp::socket&& new_socket) {
                if (ec) {
                    std::cout << "Failed to accept" << std::endl;
                    return;
                }
                std::cout << "New client accepted" << std::endl;
                std::shared_ptr<boost::asio::ip::tcp::socket> new_socket_ptr = std::make_shared<boost::asio::ip::tcp::socket>(std::move(new_socket));
                _sockets.push_back(new_socket_ptr);

                async_read_(new_socket_ptr);
                accept_clients();
            });
        }

        void handle_new_client_(void)
        {

        }

        void read_(void)
        {
            for (auto socket_ptr : _sockets) {
                boost::asio::read(*(socket_ptr.get()) , boost::asio::buffer(_recv_buf));
                if (_recv_buf[0].type == LobbyType) {
                    for (int i = 0; _recv_buf[0].lobbies[i].size != 0; i++) {
                        std::cout << "Lobby of uuid: " << _recv_buf[0].lobbies[i].uuid << std::endl;
                    }
                }
            }
            std::cout << "Read ended" << std::endl;
        }

        void async_read_(std::shared_ptr<boost::asio::ip::tcp::socket> new_socket)
        {
            std::cout << "Ready to async read" << std::endl;
            boost::asio::async_read(*(new_socket.get()), boost::asio::buffer(_recv_buf),
            boost::bind(&tcp_server::handle_read_, this, new_socket,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
        }

        void handle_read_(std::shared_ptr<boost::asio::ip::tcp::socket> new_socket,
            boost::system::error_code const& error, size_t bytes_transferred)
        {
            if ((boost::asio::error::eof == error) ||
                (boost::asio::error::connection_reset == error)) {
                std::cout << "player disconnected" << std::endl;
                std::size_t j = -1;
                for (std::size_t i = 0; i < _sockets.size(); i++) {
                    if (_sockets[i] == new_socket) {
                        j = i;
                    }
                }
                if (j != -1) {
                    _sockets.erase(_sockets.begin() + j);
                    std::cout << "socket deleted" << std::endl;
                }
                if (_sockets.size() == 0) {
                    std::cout << "vector sockets empty" << std::endl;
                }
            } else {
                std::cout << "data received from client" << std::endl;
                if (_recv_buf[0].type == LobbyType) {
                    for (int i = 0; _recv_buf[0].lobbies[i].size != 0; i++) {
                        std::cout << "Lobby of uuid: " << _recv_buf[0].lobbies[i].uuid << std::endl;
                    }
                }
                async_read_(new_socket);
            }
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
            for (auto socket_ptr : _sockets) {
                boost::asio::write(*(socket_ptr.get()), boost::asio::buffer(send_buf));
                std::cout << "data sent to client" << std::endl;
            }
            _timer.expires_from_now(boost::posix_time::milliseconds(500));
            _timer.async_wait(boost::bind(&tcp_server::send_, this));
        }
    private:
        union { boost::array <Data, 1> _recv_buf; };
        boost::asio::ip::tcp::acceptor _acceptor;
        std::vector<std::shared_ptr<boost::asio::ip::tcp::socket>> _sockets;
        boost::asio::deadline_timer _timer;
};

int main(void)
{
    boost::asio::io_service io_context;
    tcp_server server(io_context);
    io_context.run();
    return 0;
}
