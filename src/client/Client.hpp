/*
** EPITECH PROJECT, 2022
** Client
** File description:
** boost::asio
*/

#pragma once

#include <boost/uuid/uuid_generators.hpp>

#include "Common.hpp"

class Client {
    public:
        Client(std::string ip, std::size_t port)
        : _receiver_endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 10001), _socket(_io_context)
        {
            _socket.open(boost::asio::ip::udp::v4());
            _uuid = boost::uuids::random_generator()();
        }
        void sendData(enum Input action);
        void receiveData(boost::array<SpriteData, 16>& recv_buf);
        boost::uuids::uuid getUuid(void);
    private:
        boost::asio::io_context _io_context;
        boost::asio::ip::udp::endpoint _receiver_endpoint;
        boost::asio::ip::udp::socket _socket;
        std::string _ip;
        std::size_t _port;
        boost::uuids::uuid _uuid;
};
