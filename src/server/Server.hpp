/*
** EPITECH PROJECT, 2022
** Server
** File description:
** boost::asio
*/

#pragma once

#include <boost/date_time/posix_time/posix_time.hpp>

#include "ecs/Entity.hpp"
#include "ecs/Factory.hpp"
#include "ecs/Systems/DrawSystem.hpp"
#include "ecs/Systems/HealthSystem.hpp"

#include <utility>
#include <fstream>
#include <sstream>
#include <string.h>

#include "../Common.hpp"

struct Player {
    boost::asio::ip::udp::endpoint endpoint;
    boost::uuids::uuid uuid;
    std::size_t idSprite;
};

class Server {
    public:
    Server(boost::asio::io_context &io_context):
        _udp_socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 10001)),
        _acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1234)),
        _timer(io_context), _empty_uuid({})
    {
        try {
            parseWaves();
            _d = std::make_unique<DrawSystem>();
            _h = std::make_unique<HealthSystem>();
        } catch (Error &e) {
            std::cout << e.what() << std::endl;
        }
        /*
            TCP:
            acceptClients();
            send();
        */
            UDP:
            handleTimer();
            startReceive();
    }

    ~Server()
    {
        std::cout << "Shutting down the server..." << std::endl;
    }

    private:
    void parseWaves(void);
    void sendSprites(void);
    void handleReceive(const boost::system::error_code &, std::size_t);

    void handleSend(
        boost::uuids::uuid,
        const boost::array<Data, 1>,
        const boost::system::error_code &,
        std::size_t
    );
    void handleTimer(void);
    void handleInput(Action action);
    bool isNewUuid(boost::uuids::uuid uuid);
    void findPlayerSprite(Action action);
    void moveSprite(std::shared_ptr<Velocity>, enum Input);
    std::size_t setNewSpriteId(std::size_t new_id);

    // UDP

    boost::asio::ip::udp::socket _udp_socket;
    boost::asio::ip::udp::endpoint _remote_endpoint;
    std::vector<Player> _players;

    void startReceive(void);

    // TCP

    boost::asio::ip::tcp::acceptor _acceptor;
    std::vector<std::pair<boost::uuids::uuid, std::shared_ptr<boost::asio::ip::tcp::socket>>> _sockets;
    boost::uuids::uuid _empty_uuid;
    boost::array<Data, 1> _lobby_buf; // probablement transformable en boost::array<Lobby, 16>

    void acceptClients(void);
    void read(void);
    void asyncRead(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
    std::size_t findIndexFromSocket(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
    void handleRead(std::shared_ptr<boost::asio::ip::tcp::socket> socket,
        boost::system::error_code const& error, size_t bytes_transferred);
    void send(void);

    // Data, buffer, timer

    boost::array<Action, 1> _recv_buf;
    std::vector<SpriteData> _sprites;
    boost::asio::deadline_timer _timer;

    // ECS

    std::shared_ptr<Entity> createEntity(std::string, std::string, std::pair<float, float>, std::pair<float, float>, std::pair<float, float>, std::pair<float, float>, std::string, std::size_t);
    void launchWave(std::size_t);
    InitSpriteData getInitSpriteData(std::shared_ptr<Entity> &e);
    SpriteData getSpriteData(std::shared_ptr<Entity> &e);
    void initEcs(boost::uuids::uuid, std::size_t);

    std::size_t getEntityIdByUuid(Action action);

    // Factory
    std::unique_ptr<Factory> _f;

    // Systems
    std::unique_ptr<DrawSystem> _d;
    std::unique_ptr<HealthSystem> _h;

    // List of entities
    std::size_t _currentWave;
    std::vector<std::shared_ptr<Entity>> _entities;
    std::unordered_map<std::size_t, std::pair<std::size_t, std::string>> _waveConf;
};
