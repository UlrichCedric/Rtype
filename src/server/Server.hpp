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
    Server(boost::asio::io_context &io_context):
        _udp_socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 10001)),
        _acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1234)),
        _timer(io_context), _empty_uuid({})
    {
        try {
            parseWaves();
        } catch (Error &e) {
            std::cout << e.what() << std::endl;
        }
        // TCP:
        Lobby default_lobby = {{}, false, false, false, "whis", 1, 1, boost::uuids::random_generator()(), OPEN}; // provisoire
        _lobbies.push_back(default_lobby); // provisoire
        _lobbies.push_back(default_lobby); // provisoire
        _lobbies.push_back(default_lobby); // provisoire
        acceptClients();
        // send();

        /*
            UDP:
            handleTimer();
            startReceive();
        */
    }

    ~Server()
    {
        std::cout << "Shut down the server" << std::endl;
    }

    private:
    void parseWaves(void);
    void sendSprites(void);

    void handleTimer(void);
    void handleInput(Action action);
    bool isNewUuid(boost::uuids::uuid uuid);
    void findPlayerSprite(Action action);
    void moveSprite(SpriteData& sprite, enum Input input);
    std::size_t setNewSpriteId(std::size_t new_id);

    // UDP

    boost::asio::ip::udp::socket _udp_socket;
    boost::asio::ip::udp::endpoint _remote_endpoint;
    std::vector<Player> _players;

    void startReceive(void);
    void handleReceive(const boost::system::error_code &, std::size_t);
    void handleSend(
        boost::uuids::uuid,
        const boost::array<Data, 1>,
        const boost::system::error_code &,
        std::size_t
    );

    // TCP

    boost::asio::ip::tcp::acceptor _acceptor;
    std::vector<std::pair<boost::uuids::uuid, std::shared_ptr<boost::asio::ip::tcp::socket>>> _sockets;
    boost::uuids::uuid _empty_uuid;
    boost::array<Lobby, 1> _lobby_buf;
    std::vector<Lobby> _lobbies;

    void acceptClients(void);
    void asyncRead(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
    std::size_t findIndexFromSocket(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
    void handleRead(std::shared_ptr<boost::asio::ip::tcp::socket> socket,
        boost::system::error_code const& error, size_t bytes_transferred);
    void send(void);
    void sendLobbies(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
    void createLobby(Lobby &lobby);

    // Data, buffer, timer

    boost::array<Action, 1> _recv_buf;
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
