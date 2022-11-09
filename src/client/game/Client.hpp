/*
** EPITECH PROJECT, 2022
** Client
** File description:
** boost::asio
*/

#pragma once

#include <boost/thread/thread.hpp>

<<<<<<< HEAD:src/client/game/Client.hpp
#include "../../Common.hpp"
#include "../utils/Image.hpp"

class Client {
    public:
        Client(std::string ip, std::size_t port)
        : _receiver_endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 10001),
            _udp_socket(_io_context), _tcp_socket(_io_context), _player_pos({0, 0})
        {
            /*
                TCP:
                _tcp_socket.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));

                UDP:
                _udp_socket.open(boost::asio::ip::udp::v4());
                _uuid = boost::uuids::random_generator()();
                _canReceiveData = true;
                std::thread thread(&Client::handleThread, this);
                thread.detach();
            */
=======
#include <memory>
#include <fstream>

#include "../Common.hpp"
#include "Image.hpp"

class Client {
    public:
        Client(const std::string ip, const std::size_t port):
            _receiver_endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 10001),
            _socket(_io_context),
            _player_pos({0, 0}),
            _ip(ip),
            _port(port)
        {
            _socket.open(boost::asio::ip::udp::v4());
            _uuid = boost::uuids::random_generator()();
            std::thread thread(&Client::handleThread, this);
            thread.detach();
>>>>>>> client-server_link:src/client/Client.hpp
        }

        void sendData(enum Input action);
        void asyncSendData(enum Input action);
        void handleSendData(const boost::system::error_code &, std::size_t);
        void receiveData(void);
        void handleInitSpriteData(void);
        void handleSpriteData(void);
        void asyncReceiveData(void);
        void handleReceiveData(const boost::system::error_code &, std::size_t);
        void handleThread(void);
<<<<<<< HEAD:src/client/game/Client.hpp
        void setCanReceiveData(bool canReceiveData);
        void createLobby(std::string name, std::size_t size);
        void joinLobby(boost::uuids::uuid uuid);
        void writeData(void);
        void readData(void);
        std::vector<Lobby> getLobbies(void);
=======
        void setCanReceiveData(bool);
>>>>>>> client-server_link:src/client/Client.hpp

        ~Client() = default;

        boost::uuids::uuid getUuid(void);
        std::pair<float, float> getPlayerPos(void);
        std::vector<std::shared_ptr<Game::Image>> _images;

    private:
        boost::asio::io_context _io_context;
        boost::asio::ip::udp::endpoint _receiver_endpoint;
        boost::asio::ip::udp::socket _udp_socket;
        boost::asio::ip::tcp::socket _tcp_socket;
        std::string _ip;
        std::size_t _port;
        boost::uuids::uuid _uuid;
        union { boost::array<Data, 1> _recv_buf; }; // avoid Client to try to destroy _recv_buf when destructing
        std::pair<float, float> _player_pos = { 0.0, 0.0 };
        bool _canReceiveData = true;
};
