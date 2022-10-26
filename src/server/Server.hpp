/*
** EPITECH PROJECT, 2022
** Server
** File description:
** boost::asio
*/

#pragma once

#include <boost/bind/bind.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "ecs/Entity.hpp"
#include "ecs/Systems/DrawSystem.hpp"
#include "ecs/Systems/HealthSystem.hpp"
#include "Common.hpp"
#include "ecs/Factory.hpp"

// Server class
class Server {
    public:
    Server(boost::asio::io_context& io_context)
        : _socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 10001)),
        _timer(io_context) {
        initEcs();
        handleTimer();
        startReceive();
    }

    private:
    std::shared_ptr<Entity> createEntity(std::string, std::string, std::pair<float, float>, std::pair<float, float>, std::pair<float, float>);
    void startReceive(void);
    void sendSprites(void);
    void handleReceive(const boost::system::error_code& error, std::size_t /*bytes_transferred*/);
    void handleSend(boost::array<SpriteData, 16>,const boost::system::error_code&, std::size_t);
    void handleTimer(void);
    void handleInput(Action action);
    bool isNewUuid(boost::uuids::uuid uuid);
    void findPlayerSprite(Action action);
    void moveSprite(SpriteData& sprite, enum Input input);
    std::size_t setNewSpriteId(std::size_t new_id);
    void initEcs(void);

    std::size_t getEntityIdByUuid(Action action);

    boost::asio::ip::udp::socket _socket;
    boost::asio::ip::udp::endpoint _remote_endpoint;
    boost::array<Action, 1> _recv_buf;
    std::vector<std::pair<boost::uuids::uuid, std::size_t>> _players_uuid;
    std::vector<SpriteData> _sprites;
    boost::asio::deadline_timer _timer;

    // List of entities
    std::list<std::shared_ptr<Entity>> _entities;

    // Factory
    std::unique_ptr<Factory> _f;

    // Systems
    std::unique_ptr<DrawSystem> _d;
    std::unique_ptr<HealthSystem> _h;
};
