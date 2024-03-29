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
#include "ecs/Systems/HitboxSystem.hpp"

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
            _f = std::make_unique<Factory>();
            _drawinSystem = std::make_unique<DrawSystem>();
            _healthSystem = std::make_unique<HealthSystem>();
            _hitboxSystem = std::make_unique<HitboxSystem>();

            parseWaves();
        } catch (Error &e) {
            std::cout << e.what() << std::endl;
        }
        // TCP:
        acceptClients();
    }

    ~Server(void) { std::cout << "[-] Shut down the server" << std::endl; }

    private:
    void parseWaves(void);
    void sendSprites(boost::uuids::uuid);

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
    bool _isUDPLaunched = false;

    void startReceive(void);
    void handleReceive(const boost::system::error_code &, std::size_t);
    void handleSend(
        boost::uuids::uuid,
        const boost::array<Data, 1>,
        const boost::system::error_code &,
        std::size_t
    );
    void sendInitSpriteDatasToNewPlayer(Player &p);

    // this one will store the initSpriteDatas
    boost::array<Data, 1> _send_buf = {  };

    // TCP

    boost::asio::ip::tcp::acceptor _acceptor;
    std::vector<std::pair<boost::uuids::uuid, std::shared_ptr<boost::asio::ip::tcp::socket>>> _sockets;
    boost::uuids::uuid _empty_uuid;
    boost::array<Lobby, 1> _lobby_buf;
    std::vector<Lobby> _lobbies;

    // { Lobby UUID, { player1 UUID, player2 UUID... } }
    std::vector<std::pair<boost::uuids::uuid, std::vector<boost::uuids::uuid>>> _players_in_lobbies;

    void acceptClients(void);
    void asyncRead(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
    std::size_t findIndexFromSocket(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
    void handleRead(std::shared_ptr<boost::asio::ip::tcp::socket> socket,
        boost::system::error_code const& error, size_t bytes_transferred);
    void send(void);
    void sendLobbies(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
    void createLobby(Lobby &lobby);
    void joinLobby(Lobby &lobby, std::shared_ptr<boost::asio::ip::tcp::socket> socket);
    Lobby getLobbyFromUUID(boost::uuids::uuid uuid);
    void deleteCorrespondingPlayer(boost::uuids::uuid player_uuid);
    void deleteCorrespondingPlayerFromLobbies(boost::uuids::uuid player_uuid);
    boost::uuids::uuid getLobbyUuidFromPlayerUuid(boost::uuids::uuid player_uuid);
    void deleteCorrespondingSprite(std::size_t idSprite);
    boost::array<SpriteData, 16> getLobbySpriteData(boost::uuids::uuid player_uuid);
    std::vector<std::size_t> getSpritesIdFromPlayersUuid(std::vector<boost::uuids::uuid> players_uuid);
    void customizedSpriteData(boost::array<Data, 1> &send_buf, std::size_t idSprite);
    bool isPlayerInLobby(boost::uuids::uuid, boost::uuids::uuid);
    std::pair<float, float> getPlayerPositionByUuid(boost::uuids::uuid);
    Player getPlayerFromPlayerUuid(boost::uuids::uuid playerUuid);


    // Data, buffer, timer

    boost::array<Action, 1> _recv_buf;
    std::vector<SpriteData> _sprites;
    boost::asio::deadline_timer _timer;

    // ECS

    void createBullet(std::pair<float, float> position, boost::uuids::uuid playerUuid);
    std::shared_ptr<Entity> createEntity(std::string, std::string, std::pair<float, float>, std::pair<float, float>, std::pair<float, float>, std::pair<float, float>);
    InitSpriteData getInitSpriteData(std::shared_ptr<Entity> &e);
    SpriteData getSpriteData(std::shared_ptr<Entity> &e);
    void initEcs(boost::uuids::uuid);
    int getBulletNumber(boost::uuids::uuid);

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
    std::unique_ptr<DrawSystem> _drawinSystem;
    std::unique_ptr<HealthSystem> _healthSystem;
    std::unique_ptr<HitboxSystem> _hitboxSystem;

    // List of entities
    std::size_t _currentWave;
    std::map<boost::uuids::uuid, std::vector<std::shared_ptr<Entity>>> _entities;
    std::unordered_map<std::size_t, std::pair<std::size_t, std::string>> _waveConf;
};
