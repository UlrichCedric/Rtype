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

#include "../Common.hpp"

struct Player {
    boost::asio::ip::udp::endpoint endpoint;
    boost::uuids::uuid uuid;
    std::size_t idSprite;
};

class Server {
    public:
    Server(boost::asio::io_context& io_context)
        : _socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 10001)),
        _timer(io_context) {
        handleTimer();
        startReceive();
        try {
            parseWaves();
        } catch (Error &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    private:
    void parseWaves(void);
    void startReceive(void);
    void sendSprites(void);
    void handleReceive(const boost::system::error_code &, std::size_t);

    /**
     * @brief
     *
     * @param boost::uuids::uuid uuid of the client
     * @param const boost::array<Data, 1> data sent to the client
     * @param const boost::system::error_code& error code
     * @param std::size_t number of bytes received
     */
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
    void moveSprite(SpriteData& sprite, enum Input input);
    std::size_t setNewSpriteId(std::size_t new_id);

    boost::asio::ip::udp::socket _socket;
    boost::asio::ip::udp::endpoint _remote_endpoint;
    boost::array<Action, 1> _recv_buf;
    std::vector<Player> _players;
    std::vector<SpriteData> _sprites;
    boost::asio::deadline_timer _timer;

    // ECS

    std::shared_ptr<Entity> createEntity(std::string, std::string, std::pair<float, float>, std::pair<float, float>, std::pair<float, float>);
    InitSpriteData getInitSpriteData(std::shared_ptr<Entity> &e);
    SpriteData getSpriteData(std::shared_ptr<Entity> &e);
    void initEcs(void);

    /**
     * @brief Initialize new wave's sprites
     * @param size_t wave number
     * @throw Error & if size_t is negative or not saved in _waveConf
     */
    void newWave(std::size_t);
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
