/*
** EPITECH PROJECT, 2022
** Client
** File description:
** boost::asio
*/

#pragma once

#include <boost/uuid/uuid_generators.hpp>
#include <boost/thread/thread.hpp>

#include "../Common.hpp"
#include "Image.hpp"

class Client {
    public:
        Client(std::string ip, std::size_t port)
        : _receiver_endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 10001), _socket(_io_context), _player_pos({0, 0})
        {
            _socket.open(boost::asio::ip::udp::v4());
            _uuid = boost::uuids::random_generator()();
            _canReceiveData = true;
            std::thread thread(&Client::handleThread, this);
            // peut être intéressant pour tcp : boost::thread t = boost::thread(&Client::handleThread, boost::ref(socket));
            thread.detach();
        }
        void sendData(enum Input action);
        void asyncSendData(enum Input action);
        void handleSendData(const boost::system::error_code& error, std::size_t /*bytes_transferred*/);
        void receiveData(void);
        void handleInitSpriteData(void);
        void handleSpriteData(void);
        void asyncReceiveData(void);
        void handleReceiveData(const boost::system::error_code& error, std::size_t /*bytes_transferred*/);
        void handleThread(void);
        void setCanReceiveData(bool canReceiveData);

        ~Client() {  };

        boost::uuids::uuid getUuid(void);
        std::pair<float, float> getPlayerPos(void);

        /**
         * @brief our image list
         *
         */
        std::vector<Game::Image> _images;

    private:
        boost::asio::io_context _io_context;
        boost::asio::ip::udp::endpoint _receiver_endpoint;
        boost::asio::ip::udp::socket _socket;
        std::string _ip;
        std::size_t _port;
        boost::uuids::uuid _uuid;
        union { boost::array<Data, 1> _recv_buf; }; // avoid Client to try to destroy _recv_buf when destructing
        std::pair<float, float> _player_pos;
        bool _canReceiveData;
};
