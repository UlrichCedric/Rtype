/*
** EPITECH PROJECT, 2022
** Client
** File description:
** boost::asio
*/

#pragma once

#include <boost/thread/thread.hpp>

#include "../../Common.hpp"
#include "../utils/Image.hpp"
#include "Image.hpp"
#include "../../Errors.hpp"

#include <memory>
#include <fstream>

class Client {
    public:
        Client(const std::string ip, const std::size_t port):
            _receiver_endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 10001),
            _udp_socket(_io_context),
            _tcp_socket(_io_context),
            _player_pos({0, 0}),
            _ip(ip),
            _port(port)
        {
            // TCP
            _tcp_socket.connect(
                boost::asio::ip::tcp::endpoint(
                    boost::asio::ip::address::from_string("127.0.0.1"),
                    1234
                )
            );

            // UDP
            _udp_socket.open(boost::asio::ip::udp::v4());
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
        void createLobby(std::string, std::size_t);
        void joinLobby(boost::uuids::uuid);
        void writeData(void);
        void readData(void);
        std::vector<Lobby> getLobbies(void);
        void setCanReceiveData(bool);

        // utils
        std::shared_ptr<Game::Image> getImageById(std::size_t id) {
            for (auto img: _images) {
                if (img->getId() == id) {
                    return img;
                }
            }
            throw Error("Couldn't find image with given ID");
        }

        ~Client() {  };

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
