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
            _acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1234)),
            _empty_uuid({})
        {
            acceptClients();
            send();
        }

        ~tcp_server()
        {
            std::cout << "Shut down the server" << std::endl;
        }

        void acceptClients(void)
        {
            _acceptor.async_accept(
                [this] (std::error_code ec, boost::asio::ip::tcp::socket&& new_socket) {
                if (ec) {
                    std::cout << "Failed to accept" << std::endl;
                    return;
                }
                std::cout << "New client accepted" << std::endl;
                std::shared_ptr<boost::asio::ip::tcp::socket> new_socket_ptr = std::make_shared<boost::asio::ip::tcp::socket>(std::move(new_socket));
                std::pair<boost::uuids::uuid, std::shared_ptr<boost::asio::ip::tcp::socket>> pair = {{}, new_socket_ptr};
                _sockets.push_back(pair);

                asyncRead(new_socket_ptr);
                acceptClients();
            });
        }

        void read(void)
        {
            for (auto pair : _sockets) {
                boost::asio::read(*(pair.second.get()) , boost::asio::buffer(_lobby_buf));
                if (_lobby_buf[0].type == LobbyType) {
                    for (int i = 0; _lobby_buf[0].lobbies[i].size != 0; i++) {
                        std::cout << "Lobby of uuid: " << _lobby_buf[0].lobbies[i].lobby_uuid << std::endl;
                    }
                }
            }
            std::cout << "Read ended" << std::endl;
        }

        void asyncRead(std::shared_ptr<boost::asio::ip::tcp::socket> socket)
        {
            std::cout << "Ready to async read" << std::endl;
            boost::asio::async_read(*(socket.get()), boost::asio::buffer(_lobby_buf),
            boost::bind(&tcp_server::handleRead, this, socket,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
        }

        std::size_t findIndexFromSocket(std::shared_ptr<boost::asio::ip::tcp::socket> socket)
        {
            std::size_t j = -1;
            for (std::size_t i = 0; i < _sockets.size(); i++) {
                if (_sockets[i].second == socket) {
                    j = i;
                }
            }
            return j;
        }

        void handleRead(std::shared_ptr<boost::asio::ip::tcp::socket> socket,
            boost::system::error_code const& error, size_t bytes_transferred)
        {
            if ((boost::asio::error::eof == error) ||
                (boost::asio::error::connection_reset == error)) {
                std::cout << "player disconnected" << std::endl;
                std::size_t j = findIndexFromSocket(socket);
                if (j != -1) {
                    _sockets.erase(_sockets.begin() + j);
                    std::cout << "socket deleted" << std::endl;
                }
                if (_sockets.size() == 0) {
                    std::cout << "vector sockets empty" << std::endl;
                }
            } else {
                if (_lobby_buf[0].type == LobbyType) {
                    std::size_t j = findIndexFromSocket(socket);
                    if (j != -1) {
                        _sockets[j].first = _lobby_buf[0].lobbies[0].player_uuid;
                    }
                    for (int i = 0; _lobby_buf[0].lobbies[i].size != 0; i++) {
                        std::cout << "Lobby of uuid: " << _lobby_buf[0].lobbies[i].lobby_uuid
                        << "from user " << _lobby_buf[0].lobbies[i].player_uuid << std::endl;
                    }
                }
                std::cout << "List of players uuid paired with socket: " << std::endl;
                std::size_t socket_index = 0;
                for (auto pair : _sockets) {
                    std::cout << socket_index << ": " << pair.first << std::endl;
                    socket_index += 1;
                }
                asyncRead(socket);
            }
        }

        void send(void)
        {
            Lobby lobby1 = {boost::uuids::random_generator()(), true, true, "lobby1", 2, 4, boost::uuids::random_generator()(), OPEN};
            Lobby lobby2 = {boost::uuids::random_generator()(), true, true, "lobby2", 2, 4, boost::uuids::random_generator()(), OPEN};
            Lobby lobby3 = {boost::uuids::random_generator()(), true, true, "lobby3", 2, 4, boost::uuids::random_generator()(), OPEN};
            Lobby endArray = {boost::uuids::random_generator()(), false, false, "", 0, 0, boost::uuids::random_generator()(), CLOSE};
            boost::array<Lobby, 16> array_buf;
            array_buf[0] = lobby1;
            array_buf[1] = lobby2;
            array_buf[2] = lobby3;
            array_buf[3] = endArray;
            Data data = {LobbyType, {}, {}, array_buf};
            boost::array<Data, 1> send_buf = {data};
            for (auto pair : _sockets) {
                boost::asio::write(*(pair.second.get()), boost::asio::buffer(send_buf));
                std::cout << "data sent to client" << std::endl;
            }
            _timer.expires_from_now(boost::posix_time::milliseconds(500));
            _timer.async_wait(boost::bind(&tcp_server::send, this));
        }
    private:
        union { boost::array <Data, 1> _lobby_buf; };
        boost::asio::ip::tcp::acceptor _acceptor;
        std::vector<std::pair<boost::uuids::uuid, std::shared_ptr<boost::asio::ip::tcp::socket>>> _sockets;
        boost::asio::deadline_timer _timer;
        boost::uuids::uuid _empty_uuid;
};

int main(void)
{
    boost::asio::io_service io_context;
    tcp_server server(io_context);
    io_context.run();
    return 0;
}
