/*
** EPITECH PROJECT, 2022
** Client
** File description:
** boost::asio
*/

#pragma once

#include <boost/uuid/uuid_generators.hpp>
#include <boost/thread/thread.hpp>

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
        void setCanReceiveData(bool);

        ~Client() = default;

        boost::uuids::uuid getUuid(void);
        std::pair<float, float> getPlayerPos(void);
        std::vector<std::shared_ptr<Game::Image>> _images;

    private:
        boost::asio::io_context _io_context;
        boost::asio::ip::udp::endpoint _receiver_endpoint;
        boost::asio::ip::udp::socket _socket;
        std::string _ip;
        std::size_t _port;
        boost::uuids::uuid _uuid;
        union { boost::array<Data, 1> _recv_buf; }; // avoid Client to try to destroy _recv_buf when destructing
        std::pair<float, float> _player_pos = { 0.0, 0.0 };
        bool _canReceiveData = true;
};
