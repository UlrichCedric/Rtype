/*
** EPITECH PROJECT, 2022
** server
** File description:
** udp boost asio
*/

#include "Server.hpp"
#include "ecs/Components/Velocity.hpp"

void Server::parseWaves(void) {
    std::ifstream file("enemies.conf");
    std::string string = "";
    std::size_t i = 0;

    while(std::getline(file, string)) {
        if (string.empty()) {
            break;
        }
        std::size_t number = 10;
        try {
            number = std::stoi(string.substr(0, string.find(':', 0)));
        } catch (std::exception &e) {
            std::cerr << "Error parsing your enemy config file: invalid number" << std::endl;
            exit(84);
        }
        std::string name = string.substr(string.find(':', 0), string.length() - 1);
        _waveConf[i++] = std::pair<std::size_t, std::string>(number, name);
    }
}

/// @brief Async function to receive data from clients.
/// @param  No parameter
void Server::startReceive(void)
{
    _udp_socket.async_receive_from(
        boost::asio::buffer(_recv_buf), _remote_endpoint,
        boost::bind(&Server::handleReceive, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

/// @brief Function called at the start of UDP sending data informations to clients. Recursively call itself every x milliseconds.
/// @param  No parameter
void Server::handleTimer(void) {
    sendSprites();
    // Wait for next timeout.
    _timer.expires_from_now(boost::posix_time::milliseconds(10));
    _timer.async_wait(boost::bind(&Server::handleTimer, this));
}

bool Server::isNewUuid(boost::uuids::uuid uuid)
{
    std::vector<boost::uuids::uuid> uuids;

    for (Player player : _players) {
        uuids.push_back(player.uuid);
    }
    if (std::find(uuids.begin(), uuids.end(), _recv_buf[0].uuid) != uuids.end()) {
        return false;
    }
    return true;
}

std::size_t Server::setNewSpriteId(std::size_t new_id)
{
    if (new_id == 0) {
        new_id = _sprites.size() + 1;
    }
    for (SpriteData sprite :_sprites) {
        if (sprite.id == new_id) {
            return (setNewSpriteId(new_id + 1));
        }
    }
    return (new_id);
}

void Server::moveSprite(SpriteData& sprite, enum Input input)
{
    switch (input) {
        case UP: sprite.coords.second -= 12; break;
        case DOWN: sprite.coords.second += 12; break;
        case LEFT: sprite.coords.first -= 12; break;
        case RIGHT: sprite.coords.first += 12; break;
        default: break;
    }
    if (sprite.coords.first < -10) {
        sprite.coords.first = -10;
    }
    if (sprite.coords.first > 1185) {
        sprite.coords.first = 1185;
    }
    if (sprite.coords.second < -15) {
        sprite.coords.second = -15;
    }
    if (sprite.coords.second > 850) {
        sprite.coords.second = 850;
    }
}

void Server::findPlayerSprite(Action action)
{
    std::size_t id_sprite_player = 0;

    for (Player& player : _players) {
        if (action.uuid == player.uuid) {
            id_sprite_player = player.idSprite;
            break;
        }
    }
    if (id_sprite_player == 0) {
        return;
    }
    for (SpriteData& sprite : _sprites) {
        if (sprite.id == id_sprite_player) {
            moveSprite(sprite, action.input);
        }
    }
}

/**
 * @brief Analyses the player input
 *
 * @param action { input key the player sent, UUID of the player }
 */
void Server::handleInput(Action action)
{
    if (action.input != NONE) {
        if (action.input == SPACE) {
            /* shoot projectile */
        } else {
            findPlayerSprite(action);
        }
    }
}

/**
 * @brief Inverts the main client player with the first object of send_buf
 *
 * @param send_buf buffer to be sent
 * @param idSprite the ID of the sprite you want to be first
 */
void Server::customizedSpriteData(boost::array<Data, 1> &send_buf, std::size_t idSprite)
{
    int j = -1;

    for (std::size_t i = 0; i < send_buf[0].spriteDatas[i].id != 0; i++) {
        if (send_buf[0].spriteDatas[i].id == idSprite) {
            j = i;
            break;
        }
    }

    if (j != -1) {
        SpriteData first = send_buf[0].spriteDatas[j];
        SpriteData other = send_buf[0].spriteDatas[0];
        send_buf[0].spriteDatas[0] = first;
        send_buf[0].spriteDatas[j] = other;
    }
}

/**
 * @brief get a vector of sprite id for the other players in the lobby
 *
 * @param players_uuid the players in the lobby
 * @return std::vector<std::size_t> a vector containing every player's sprite id
 */
std::vector<std::size_t> Server::getSpritesIdFromPlayersUuid(std::vector<boost::uuids::uuid> players_uuid)
{
    std::vector<std::size_t> idSprites;

    for (auto player : _players) {
        for (auto uuid : players_uuid) {
            if (player.uuid == uuid) {
                idSprites.push_back(player.idSprite);
            }
        }
    }
    return idSprites;
}

/**
 * @brief get spriteData with only the players of the given player lobby
 *
 * @param player_uuid player of the lobby
 * @return boost::array<SpriteData, 16> spriteData from the other players in the lobby
 */
boost::array<SpriteData, 16> Server::getLobbySpriteData(boost::uuids::uuid player_uuid)
{
    boost::uuids::uuid lobby_uuid = getLobbyUuidFromPlayerUuid(player_uuid);
    std::vector<boost::uuids::uuid> lobby_players_uuid;

    for (auto players_in_lobby : _players_in_lobbies) {
        if (players_in_lobby.first == lobby_uuid) {
            lobby_players_uuid = players_in_lobby.second;
        }
    }
    std::vector<std::size_t> idSprites = getSpritesIdFromPlayersUuid(lobby_players_uuid);
    SpriteData endArray = { 0, { 0.0, 0.0 }, 0 };
    boost::array<SpriteData, 16> array_buf = { endArray };

    for (int i = 0, j = 0; i <= _sprites.size(); i++) {
        if (j == idSprites.size() || i == _sprites.size() || i == 15) {
            array_buf[j] = endArray;
            break;
        }
        for (auto idSprite : idSprites) {
            if (_sprites[i].id == idSprite) {
                array_buf[j++] = _sprites[i];
            }
        }
    }
    return array_buf;
}

/**
 * @brief send spriteDatas to the client
 *
 */
void Server::sendSprites(void)
{
    for (Player player: _players) {
        boost::array<SpriteData, 16> array_buf = getLobbySpriteData(player.uuid);

        int i = 0;
        for (i; array_buf[i].id != 0; ++i);
        for (auto e: _entities) {
            array_buf[i] = getSpriteData(e);
        }

        Data data = { SpriteDataType, array_buf, {}, {} };
        boost::array<Data, 1> send_buf = {data};

        customizedSpriteData(send_buf, player.idSprite);

        _udp_socket.async_send_to(
            boost::asio::buffer(send_buf),
            player.endpoint,
            boost::bind(
                &Server::handleSend,
                this,
                player.uuid,
                send_buf,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred
            )
        );
    }
}

/**
 * @brief UDP: receives new players and player input
 *
 * @param error if any
 */
void Server::handleReceive(const boost::system::error_code &error, std::size_t)
{
    if (!error) {
        if (isNewUuid(_recv_buf[0].uuid)) {
            std::cout << "[+] New player !" << std::endl;
            Player new_player_info = {_remote_endpoint, _recv_buf[0].uuid, setNewSpriteId(0)};
            _players.push_back(new_player_info);
            SpriteData player = { new_player_info.idSprite, { 800.0, 400.0 }, 100 };
            _sprites.push_back(player);
            initEcs();
        }
        handleInput(_recv_buf[0]);
    }
    startReceive();
}

/**
 * @brief Verify what you're sending to the client once sent
 *
 */
void Server::handleSend(
    boost::uuids::uuid uuidReceiver,
    const boost::array<Data, 1> send_buf,
    const boost::system::error_code& /*error*/,
    std::size_t /*bytes_transferred*/
) {
    if (send_buf.size() == 0) {
        std::cerr << "Empty buffer sent" << std::endl;
        return;
    }

    std::string type = "undefined";
    if (send_buf[0].type == InitSpriteDataType) {
        type = "InitSpriteData";
    } else if (send_buf[0].type == SpriteDataType) {
        type = "SpriteData";
    }
    // std::cout << type << " sent to " << uuidReceiver << std::endl;
}

// TCP

/**
 * @brief TCP: Accept new clients
 *
 */
void Server::acceptClients(void)
{
    _acceptor.async_accept(
        [this] (std::error_code ec, boost::asio::ip::tcp::socket&& new_socket) {
        if (ec) {
            std::cout << "Failed to accept" << std::endl;
            return;
        }
        std::cout << "[+] New client accepted" << std::endl;
        std::shared_ptr<boost::asio::ip::tcp::socket> new_socket_ptr = std::make_shared<boost::asio::ip::tcp::socket>(std::move(new_socket));
        std::pair<boost::uuids::uuid, std::shared_ptr<boost::asio::ip::tcp::socket>> pair = {{}, new_socket_ptr};
        _sockets.push_back(pair);
        asyncRead(new_socket_ptr);
        acceptClients();
    });
}

void Server::asyncRead(std::shared_ptr<boost::asio::ip::tcp::socket> socket)
{
    boost::asio::async_read(*(socket.get()), boost::asio::buffer(_lobby_buf),
    boost::bind(&Server::handleRead, this, socket,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

std::size_t Server::findIndexFromSocket(std::shared_ptr<boost::asio::ip::tcp::socket> socket)
{
    int j = -1;
    for (std::size_t i = 0; i < _sockets.size(); i++) {
        if (_sockets[i].second == socket) {
            j = i;
        }
    }
    return j;
}

/**
 * @brief Get Lobby object from lobby uuid
 *
 * @param uuid of the lobby you're looking for
 * @return Corresponding lobby object
 */
Lobby Server::getLobbyFromUUID(boost::uuids::uuid uuid)
{
    Lobby lobby = {{}, false, false, false, "", 0, 0, uuid, CLOSE};
    for (auto l : _lobbies) {
        if (l.lobby_uuid == uuid) {
            lobby = l;
            break;
        }
    }
    if (!lobby.askForLobbies && !lobby.create && !lobby.join) {
        std::cout << "Lobby introuvable" << std::endl;
    }
    return lobby;
}

/**
 * @brief gets Lobby UUID from a UUID of a player in this lobby
 *
 * @param player_uuid the player UUID
 * @return boost::uuids::uuid the UUID of the lobby the player is in
 */
boost::uuids::uuid Server::getLobbyUuidFromPlayerUuid(boost::uuids::uuid player_uuid)
{
    for (auto players_in_lobby: _players_in_lobbies) {
        for (auto uuid : players_in_lobby.second) {
            if (uuid == player_uuid) {
                return (players_in_lobby.first);
            }
        }
    }
    return (_empty_uuid);
}

void Server::deleteCorrespondingPlayerFromLobbies(boost::uuids::uuid player_uuid)
{
    boost::uuids::uuid lobby_uuid = getLobbyUuidFromPlayerUuid(player_uuid);

    for (auto &lobby : _lobbies) {
        if (lobby.lobby_uuid == lobby_uuid) {
            lobby.nb_players -= 1;
            if (lobby.nb_players < 0) {
                lobby.nb_players = 0;
            }
        }
    }

    for (auto &players_in_lobby: _players_in_lobbies) {
        for (std::size_t i = 0; i < players_in_lobby.second.size(); i++) {
            if (players_in_lobby.second[i] == player_uuid) {
                players_in_lobby.second.erase(players_in_lobby.second.begin() + i);
                break;
            }
        }
    }
}

void Server::deleteCorrespondingSprite(std::size_t idSprite)
{
    int j = -1;

    for (std::size_t i = 0; i < _sprites.size(); i++) {
        if (_sprites[i].id == idSprite) {
            j = i;
            break;
        }
    }
    if (j != -1) {
        _sprites.erase(_sprites.begin() + j);
    }
}

void Server::deleteCorrespondingPlayer(boost::uuids::uuid player_uuid)
{
    int j = -1;

    for (std::size_t i = 0; i < _players.size(); i++) {
        if (_players[i].uuid == player_uuid) {
            j = i;
            break;
        }
    }
    if (j != -1) {
        deleteCorrespondingSprite(_players[j].idSprite);
        _players.erase(_players.begin() + j);
        deleteCorrespondingPlayerFromLobbies(player_uuid);
    }
}

void Server::handleRead(std::shared_ptr<boost::asio::ip::tcp::socket> socket,
    boost::system::error_code const& error, size_t bytes_transferred)
{
    if ((boost::asio::error::eof == error) ||
        (boost::asio::error::connection_reset == error)) {
        std::cout << "[-] Player disconnected" << std::endl;
        int j = findIndexFromSocket(socket);
        if (j != -1) {
            deleteCorrespondingPlayer(_sockets[j].first);
            _sockets.erase(_sockets.begin() + j);
            std::cout << "[-] socket deleted" << std::endl;
        }
        if (_sockets.size() == 0) {
            std::cout << "[~] Vector sockets empty" << std::endl;
        }
    } else if (!error) {
        int j = findIndexFromSocket(socket);
        Lobby lobby = _lobby_buf[0];
        if (j != -1 && _sockets[j].first == _empty_uuid) {
            _sockets[j].first = lobby.player_uuid;
            // std::cout << "socket linked with player uuid " << lobby.player_uuid << std::endl;
        }
        if (lobby.askForLobbies) {
            sendLobbies(socket);
        } else if (lobby.create) {
            createLobby(lobby);
        } else if (lobby.join) {
            boost::uuids::uuid current_player_uuid = lobby.player_uuid;
            lobby = getLobbyFromUUID(lobby.lobby_uuid);
            lobby.player_uuid = current_player_uuid;
            joinLobby(lobby, socket);
        }
        asyncRead(socket);
    }
}

void Server::sendLobbies(std::shared_ptr<boost::asio::ip::tcp::socket> socket)
{
    boost::array<Lobby, 16> buf_lobbies;
    Lobby endLobby = {{}, false, false, false, "", 0, 0, {}, CLOSE};
    for (size_t i = 0; i <= _lobbies.size(); i++) {
        if (i == 15) {
            std::cout << "Too much lobbies, maximum is 15" << std::endl;
            buf_lobbies[i] = endLobby;
            break;
        }
        if (i == _lobbies.size()) {
            buf_lobbies[i] = endLobby;
        } else {
            buf_lobbies[i] = _lobbies[i];
        }
    }
    Data data = {LobbyType, {}, {}, buf_lobbies};
    boost::array<Data, 1> send_buf = {data};
    boost::system::error_code error;
    boost::asio::write(*(socket.get()), boost::asio::buffer(send_buf), error);
    if (error) {
        std::cout << "[!] Sending lobbies error: " << error.message() << std::endl;
    }
}

void Server::createLobby(Lobby &lobby)
{
    _lobbies.push_back(lobby);
}

void Server::joinLobby(Lobby &joined_lobby, std::shared_ptr<boost::asio::ip::tcp::socket> joiner_socket)
{
    bool lobbyFound = joined_lobby.create;
    bool lobbyExist = false;
    bool playerExist = false;
    bool lobbyOpen = joined_lobby.nb_players < joined_lobby.size;
    bool playerNotInOtherLobby = true;
    for (auto lobby : _lobbies) {
        if (lobby.lobby_uuid == joined_lobby.lobby_uuid) {
            lobbyExist = true;
        }
    }
    for (auto socket : _sockets) {
        if (socket.first == joined_lobby.player_uuid) {
            playerExist = true;
        }
    }
    for (auto players_in_lobby : _players_in_lobbies) {
        for (auto player_uuid : players_in_lobby.second) {
            if (player_uuid == joined_lobby.player_uuid) {
                playerNotInOtherLobby = false;
            }
        }
    }
    boost::array<int, 1> response = {lobbyExist && playerExist && lobbyOpen && playerNotInOtherLobby && lobbyFound};
    if (!lobbyFound) std::cout << "[-] Aucun lobby ne possède cette uuid" << std::endl;
    else if (!lobbyExist) std::cout << "[-] Tentative de connexion à un lobby inexistant" << std::endl;
    else if (!playerExist) std::cout << "[-] Joueur inexistant (" << joined_lobby.player_uuid << ") essaie de rejoindre un lobby" << std::endl;
    else if (!lobbyOpen) std::cout << "[-] Tentative de connexion à un lobby injoignable" << std::endl;
    else if (!playerNotInOtherLobby) std::cout << "[-] Le joueur est déjà connecté à un autre lobby" << std::endl;
    boost::system::error_code error;
    boost::asio::write(*(joiner_socket.get()), boost::asio::buffer(response), error);
    if (!error) {
        if (!response[0]) {
            std::cout << "[-] Response FORBIDDEN sent" << std::endl;
            return;
        }
        std::cout << "[+] Response OK sent" << std::endl;
        for (auto &lobby : _lobbies) {
            if (lobby.lobby_uuid == joined_lobby.lobby_uuid) {
                lobby.nb_players++;
            }
        }
        bool lobbyFound = false;
        for (auto &players_in_lobby : _players_in_lobbies) {
            if (players_in_lobby.first == joined_lobby.lobby_uuid) {
                if (players_in_lobby.second.size() < joined_lobby.size) {
                    players_in_lobby.second.push_back(joined_lobby.player_uuid);
                }
                lobbyFound = true;
                break;
            }
        }
        if (!lobbyFound) {
            std::pair<boost::uuids::uuid, std::vector<boost::uuids::uuid>> new_lobby = {joined_lobby.lobby_uuid, {joined_lobby.player_uuid}};
            _players_in_lobbies.push_back(new_lobby);
        }
        // UDP:
        handleTimer();
        startReceive();
    } else {
        std::cerr << "[-] Sent ERROR response: " << error.message() << std::endl;
    }
}

void Server::send(void)
{
    Lobby lobby1 = {boost::uuids::random_generator()(), true, true, false, "lobby1", 2, 4, boost::uuids::random_generator()(), OPEN};
    Lobby lobby2 = {boost::uuids::random_generator()(), true, true, false, "lobby2", 2, 4, boost::uuids::random_generator()(), OPEN};
    Lobby lobby3 = {boost::uuids::random_generator()(), true, true, false, "lobby3", 2, 4, boost::uuids::random_generator()(), OPEN};
    Lobby endArray = {boost::uuids::random_generator()(), false, false, false, "", 0, 0, boost::uuids::random_generator()(), CLOSE};
    boost::array<Lobby, 16> array_buf;
    array_buf[0] = lobby1;
    array_buf[1] = lobby2;
    array_buf[2] = lobby3;
    array_buf[3] = endArray;
    Data data = {LobbyType, {}, {}, array_buf};
    boost::array<Data, 1> send_buf = {data};

    for (auto pair : _sockets) {
        boost::asio::write(*(pair.second.get()), boost::asio::buffer(send_buf));
        std::cout << "data sent to client" << std::endl;
    }
    _timer.expires_from_now(boost::posix_time::milliseconds(500));
    _timer.async_wait(boost::bind(&Server::send, this));
}

/**
 * @brief Creates a new entity with the given parameters
 *
 * @param templ template (see src/server/ecs/entities.conf)
 * @param path texture path
 * @param velocity { x, y } as float
 * @param position { x, y } as float
 * @param scale { x, y } as float
 * @return std::shared_ptr<Entity> the newly created entity
 */
std::shared_ptr<Entity> Server::createEntity(
    std::string templ,
    std::string path,
    std::pair<float, float> velocity = { 0.0, 0.0 },
    std::pair<float, float> position = { -1.0, -1.0 },
    std::pair<float, float> size = { -1.0, -1.0 },
    std::pair<float, float> scale = { 1.0, 1.0 }
) {
    std::shared_ptr<Entity> e = _f->createEntity(templ);

    try {
        if (e->has(DRAWABLE) && !path.empty()) {
            auto eDraw = std::dynamic_pointer_cast<Drawable>(e->getComponent(DRAWABLE));
            eDraw->setSprite(path);
            eDraw->setSize(size);
        }
        if (e->has(VELOCITY) && velocity.first != 0.0 && velocity.second != 0.0) {
            auto eVel = std::dynamic_pointer_cast<Velocity>(e->getComponent(VELOCITY));
            eVel->setXVelocity(velocity.first);
            eVel->setYVelocity(velocity.second);
        }
        if (e->has(SCALE) && scale.first != 1.0 && scale.second != 1.0) {
            auto eScale = std::dynamic_pointer_cast<Scale>(e->getComponent(SCALE));
            eScale->setXScale(scale.first);
            eScale->setYScale(scale.second);
        }
        if (e->has(POSITION) && position.first != -1 && position.second != -1) {
            auto ePos = std::dynamic_pointer_cast<Position>(e->getComponent(POSITION));
            ePos->setXPos(position.first);
            ePos->setYPos(position.second);
        }
    } catch (Error &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return e;
}

/**
 * @brief Initializes new player ennemy sprites
 *
 */
void Server::initEcs(void)
{
    InitSpriteData endArray = { 0, "", { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } };
    boost::array<InitSpriteData, 16> buffer = { endArray }; // Initialize send_buf to empty array

    try {
        for (int i = 0; i < 3; ++i) {
            _entities.push_back(createEntity("Enemy", "assets/sprites/enemy2.png", { -0.1, 0.0 }, { 1100.0 + (i * 30), 300.0 }, { 33.0, 33.0 }, { 3.0, 3.0 }));
        }

        std::size_t i = 0;

        for (auto entity: _entities) {
            // +100 to differenciate ennemies (id > 100) from other players (id < 100)
            entity->setId(entity->getId() + 100);
            buffer[i++] = getInitSpriteData(entity);
        }

        buffer[i] = endArray;
        Data data = { InitSpriteDataType, {  }, buffer, {  } };
        boost::array<Data, 1> send_buf = { data };

        //* Uncomment the following lines to display the IDs of what you're sending to the client
        // for (int i = 0; send_buf[0].initSpriteDatas[i].id != 0; ++i) {
        //     std::cout << "sending id: " << send_buf[0].initSpriteDatas[i].id << std::endl;
        // }

        for (Player player : _players) {
            _udp_socket.async_send_to(
                boost::asio::buffer(send_buf), player.endpoint,
                boost::bind(
                    &Server::handleSend,
                    this,
                    player.uuid,
                    send_buf,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred
                )
            );
        }
    } catch (std::exception &e) {
        std::cerr << "[-] Error: " << e.what() << std::endl;
    }
}

/**
 * @brief Gets a spriteData object from an Entity
 *
 * @param e the given entity
 * @return SpriteData the new SpriteData object
 */
SpriteData Server::getSpriteData(std::shared_ptr<Entity> &e) {
    if (!e.get()->has(DRAWABLE)) {
        throw Error("Couldn't find sprite");
    }

    try {
        auto pos = std::dynamic_pointer_cast<Position>(e.get()->getComponent(POSITION));
        auto health = std::dynamic_pointer_cast<Health>(e.get()->getComponent(HEALTH));
        SpriteData s = {
            e.get()->getId() + 100, // +100 to make a difference between other player (id < 100) and enemies (id > 100)
            pos.get()->getPos(),
            health.get()->getHp()
        };

        return s;
    } catch (std::exception &e) {
        throw Error(e.what());
    }
}

/**
 * @brief Gets a initSpriteData object from an Entity
 *
 * @param e the given entity
 * @return InitSpriteData the new initSpriteData object
 */
InitSpriteData Server::getInitSpriteData(std::shared_ptr<Entity> &e) {
    if (!e->has(DRAWABLE)) {
        throw Error("Couldn't find sprite");
    }

    try {
        auto draw = std::dynamic_pointer_cast<Drawable>(e->getComponent(DRAWABLE));
        auto pos = std::dynamic_pointer_cast<Position>(e->getComponent(POSITION));
        auto scale = std::dynamic_pointer_cast<Scale>(e->getComponent(SCALE));
        auto health = std::dynamic_pointer_cast<Health>(e->getComponent(HEALTH));

        InitSpriteData s = {
            .id = e->getId(),               // get the id of the sprite
            .coords = pos->getPos(),        // get the position of the sprite
            .scale = scale->getScale(),     // get the scale of the sprite
            .maxSize = draw->getSize(),     // get the max coordinates of the rect
            .health = health->getHp(),      // get the health
        };
        strcpy(s.path, draw->getPath().c_str());

        return s;
    } catch (std::exception &e) {
        throw Error(e.what());
    }
}

/**
 * @brief returns the ID of a sprite from its UUID
 *
 * @param action containing the UUID of the sprite
 * @return std::size_t the ID of the sprite you're looking for
 */
std::size_t Server::getEntityIdByUuid(Action action)
{
    std::shared_ptr<Uuid> u;

    for (auto entity: _entities) {
        /*
            If this entity doesn't have any UUID, just continue to the next one
        */
        if (!entity.get()->has(UUID)) {
            continue;
        }
        try {
            u = std::dynamic_pointer_cast<Uuid>(entity.get()->getComponent(UUID));
        } catch (std::exception &e) {
            /*
                For any reason, if the first verification failed, and this entity
                still doesn't have any UUID, just continue to the next one
            */
            continue;
        }

        if (u->getUuid() == boost::uuids::to_string(action.uuid)) {
            return entity.get()->getId();
        }
    }
    throw Error("Entity not found");
}
