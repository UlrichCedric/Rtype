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

class Client {
    public:
        Client(std::string ip, std::size_t port)
        : _receiver_endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 10001),
            _udp_socket(_io_context), _tcp_socket(_io_context), _player_pos({0, 0}), _empty_uuid({})
        {
            // TCP:
            _tcp_socket.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));
            getLobbies();

            /*
                UDP:
                _udp_socket.open(boost::asio::ip::udp::v4());
                _uuid = boost::uuids::random_generator()();
                _canReceiveData = true;
                std::thread thread(&Client::handleThread, this);
                thread.detach();
            */
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
        void createLobby(std::string name, std::size_t size);
        void joinLobby(boost::uuids::uuid uuid);
        void writeLobbyData(bool ask, bool create, bool join, std::string name = "", std::size_t nb_players = 0, std::size_t size = 0, boost::uuids::uuid lobby_uuid = {});
        void readData(void);
        std::vector<Lobby> getLobbies(void);
        void asyncGetLobbies(void);
        void handleGetLobbies(boost::system::error_code const& error, size_t bytes_transferred);

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
        boost::asio::ip::udp::socket _udp_socket;
        boost::asio::ip::tcp::socket _tcp_socket;
        std::string _ip;
        std::size_t _port;
        boost::uuids::uuid _uuid;
        boost::uuids::uuid _empty_uuid;
        union { boost::array<Data, 1> _recv_buf; }; // avoid Client to try to destroy _recv_buf when destructing
        std::pair<float, float> _player_pos;
        bool _canReceiveData;
};
