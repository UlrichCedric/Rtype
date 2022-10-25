/*
** EPITECH PROJECT, 2022
** Server
** File description:
** boost::asio
*/

#pragma once

#include <boost/date_time/posix_time/posix_time.hpp>

#include "Common.hpp"

typedef struct Player {
    boost::asio::ip::udp::endpoint endpoint;
    boost::uuids::uuid uuid;
    std::size_t idSprite;
} Player;

class Server {
   public:
    Server(boost::asio::io_context& io_context)
        : _socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 10001)),
        _timer(io_context) {
        handleTimer();
        startReceive();
    }

   private:
    void startReceive(void);
    void sendSprites(void);
    void handleReceive(const boost::system::error_code& error,
                       std::size_t /*bytes_transferred*/);
    void handleSend(boost::uuids::uuid uuidReceiver,
                    const boost::system::error_code& /*error*/,
                    std::size_t /*bytes_transferred*/);
    void handleTimer(void);
    void handleInput(Action action);
    bool isNewUuid(boost::uuids::uuid uuid);
    void findPlayerSprite(Action action);
    void moveSprite(SpriteData& sprite, enum Input input);
    std::size_t setNewSpriteId(std::size_t new_id);

    boost::asio::ip::udp::socket _socket;
    boost::asio::ip::udp::endpoint _remote_endpoint;
    boost::array<Action, 1> _recv_buf;
    std::vector<Player> _players;
    std::vector<SpriteData> _sprites;
    boost::asio::deadline_timer _timer;
};
