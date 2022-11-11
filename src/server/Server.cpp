/*
** EPITECH PROJECT, 2022
** server
** File description:
** udp boost asio
*/

#include "Server.hpp"

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

    std::cout << "Testing parsing on enemies.conf:" << std::endl;
    for (auto [key, value]: _waveConf) {
        std::cout << "For key [" << key << "] = " << value.first << ", " << value.second << std::endl;
    }
    std::cout << "Testing finished" << std::endl;
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
        case UP: sprite.coords.second -= 10; break;
        case DOWN: sprite.coords.second += 10; break;
        case LEFT: sprite.coords.first -= 10; break;
        case RIGHT: sprite.coords.first += 10; break;
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
    if (sprite.coords.second > 870) {
        sprite.coords.second = 870;
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

void Server::sendSprites(void)
{
    SpriteData endArray = { 0, { 0.0, 0.0 }, 0 };
    boost::array<SpriteData, 16> array_buf = { endArray };
    for (int i = 0; i <= _sprites.size(); i++) {
        if (i == 15) {
            /*
                Provisoire, c'est au cas où il y ait + que 16 sprites, pour éviter le crash
            */
            std::cout << "/!\\ Agrandir la boost::array SpriteData /!\\" << std::endl;
            array_buf[i] = endArray;
            break;
        }
        if (i == _sprites.size()) {
            array_buf[i] = endArray;
        } else {
            array_buf[i] = _sprites[i];
        }
    }
    boost::array<InitSpriteData, 16> empty_array;
    Data data = {SpriteDataType, array_buf};
    boost::array<Data, 1> send_buf = {data};
    for (Player player : _players) {
        std::cout << "async send to " << player.uuid << std::endl;
        _udp_socket.async_send_to(
            boost::asio::buffer(send_buf), player.endpoint,
            boost::bind(&Server::handleSend, this, player.uuid, send_buf,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }
}

/**
 * @brief When received a message from the client
 *
 * @param error if any
 * @param std::size_t byte size
 */
void Server::handleReceive(const boost::system::error_code &error, std::size_t bytes)
{
    if (error || bytes == 0) {
        return;
    }
    std::cout << "Received: " << _recv_buf[0].input << " from " << _recv_buf[0].uuid << std::endl;
    if (isNewUuid(_recv_buf[0].uuid)) {
        std::cout << "New player with UUID" << _recv_buf[0].uuid << std::endl;
        Player new_player_info = { _remote_endpoint, _recv_buf[0].uuid, setNewSpriteId(0) };
        _players.push_back(new_player_info);
        SpriteData player = { new_player_info.idSprite, { 800.0, 400.0 }, 100 };
        std::cout << "before Init ECS" << std::endl;
        initEcs(_recv_buf[0].uuid);
    }
    handleInput(_recv_buf[0]);
    startReceive();
}

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
    std::cout << type << " sent to " << uuidReceiver << std::endl;
}

// TCP

void Server::acceptClients(void)
{
    _acceptor.async_accept(
        [this] (std::error_code ec, boost::asio::ip::tcp::socket&& new_socket) {
        if (ec) {
            std::cout << "Failed to accept" << std::endl;
            return;
        }
        std::cout << "New client accepted" << std::endl;
        std::shared_ptr<boost::asio::ip::tcp::socket> new_socket_ptr = std::make_shared<boost::asio::ip::tcp::socket>(std::move(new_socket));
        std::pair<boost::uuids::uuid, std::shared_ptr<boost::asio::ip::tcp::socket>> pair = {{}, new_socket_ptr};
        _sockets.push_back(pair);
        asyncRead(new_socket_ptr);
        acceptClients();
    });
}

void Server::read(void)
{
    for (auto pair : _sockets) {
        boost::asio::read(*(pair.second.get()) , boost::asio::buffer(_lobby_buf));
        if (_lobby_buf[0].type == LOBBYTYPE) {
            for (int i = 0; _lobby_buf[0].lobbies[i].size != 0; i++) {
                std::cout << "Lobby of uuid: " << _lobby_buf[0].lobbies[i].lobby_uuid << std::endl;
            }
        }
    }
    std::cout << "Read ended" << std::endl;
}

void Server::asyncRead(std::shared_ptr<boost::asio::ip::tcp::socket> socket)
{
    std::cout << "Ready to async read" << std::endl;
    boost::asio::async_read(*(socket.get()), boost::asio::buffer(_lobby_buf),
    boost::bind(&Server::handleRead, this, socket,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

std::size_t Server::findIndexFromSocket(std::shared_ptr<boost::asio::ip::tcp::socket> socket)
{
    std::size_t j = -1;
    for (std::size_t i = 0; i < _sockets.size(); i++) {
        if (_sockets[i].second == socket) {
            j = i;
        }
    }
    return j;
}

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

void Server::handleRead(std::shared_ptr<boost::asio::ip::tcp::socket> socket,
    boost::system::error_code const& error, size_t bytes_transferred)
{
    if ((boost::asio::error::eof == error) ||
        (boost::asio::error::connection_reset == error)) {
        std::cout << "player disconnected" << std::endl;
        std::size_t j = findIndexFromSocket(socket);
        if (j != -1) {
            _sockets.erase(_sockets.begin() + j);
            std::cout << "socket deleted" << std::endl;
        }
        if (_sockets.size() == 0) {
            std::cout << "vector sockets empty" << std::endl;
        }
    } else {
        std::size_t j = findIndexFromSocket(socket);
        Lobby lobby = _lobby_buf[0];
        if (j != -1 && _sockets[j].first == _empty_uuid) {
            _sockets[j].first = lobby.player_uuid;
            std::cout << "socket linked with player uuid " << lobby.player_uuid << std::endl;
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
    if (!error) {
        std::cout << "Lobbies sent" << std::endl;
    } else {
        std::cout << "send Lobbies error: " << error.message() << std::endl;
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
    if (!lobbyFound) std::cout << "Aucun lobby ne possède cette uuid" << std::endl;
    else if (!lobbyExist) std::cout << "Tentative de connexion à un lobby inexistant" << std::endl;
    else if (!playerExist) std::cout << "Joueur inexistant (" << joined_lobby.player_uuid << ") essaie de rejoindre un lobby" << std::endl;
    else if (!lobbyOpen) std::cout << "Tentative de connexion à un lobby injoignable" << std::endl;
    else if (!playerNotInOtherLobby) std::cout << "Le joueur est déjà connecté à un autre lobby" << std::endl;
    boost::system::error_code error;
    boost::asio::write(*(joiner_socket.get()), boost::asio::buffer(response), error);
    if (!error) {
        std::cout << "Response " << response[0] << " sent" << std::endl;
        for (auto &lobby : _lobbies) {
            if (lobby.lobby_uuid == joined_lobby.lobby_uuid) {
                lobby.nb_players += 1;
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
    } else {
        std::cout << "sent response error: " << error.message() << std::endl;
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
    Data data = { LOBBYTYPE, {}, {}, array_buf };
    boost::array<Data, 1> send_buf = { data };

    for (auto pair : _sockets) {
        boost::asio::write(*(pair.second.get()), boost::asio::buffer(send_buf));
        std::cout << "data sent to client" << std::endl;
    }

    _timer.expires_from_now(boost::posix_time::milliseconds(500));
    _timer.async_wait(boost::bind(&Server::send, this));
}

// ECS

std::shared_ptr<Entity> Server::createEntity(
    std::string templ,
    std::string path,
    std::pair<float, float> velocity,
    std::pair<float, float> position = { -1.0, -1.0 },
    std::pair<float, float> scale = { 1.0, 1.0 }
) {
    std::shared_ptr<Entity> e = _f.get()->createEntity(templ);

    try {
        auto eDraw = std::dynamic_pointer_cast<Drawable>(e.get()->getComponent(DRAWABLE));
        if (eDraw != nullptr && !path.empty()) {
            eDraw->setSprite(path);
        }
        auto eVel = std::dynamic_pointer_cast<Velocity>(e.get()->getComponent(VELOCITY));
        if (eVel != nullptr) {
            eVel->setXVelocity(velocity.first);
            eVel->setYVelocity(velocity.second);
        }
        auto eScale = std::dynamic_pointer_cast<Scale>(e.get()->getComponent(SCALE));
        if (eScale != nullptr) {
            eScale->setXScale(scale.first);
            eScale->setYScale(scale.second);
        }
        auto ePos = std::dynamic_pointer_cast<Position>(e.get()->getComponent(POSITION));
        if (ePos != nullptr && position.first != -1 && position.second != -1) {
            ePos->setXPos(position.first);
            ePos->setYPos(position.second);
        }
    } catch (Error &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return e;
}

void Server::initEcs(void)
{
    _f = std::make_unique<Factory>();
    _d = std::make_unique<DrawSystem>();
    _h = std::make_unique<HealthSystem>();

    InitSpriteData endArray = { 0, "", { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } };
    boost::array<InitSpriteData, 16> buffer = { endArray }; // Initialize send_buf to empty array

    try {
        std::shared_ptr<Entity> e1 = createEntity("Background", "../../assets/paralax/back.png", { -1.0, 0.0 }, { -1.0, -1.0 }, { 5.0, 6.0 });
        std::shared_ptr<Entity> e2 = createEntity("Background", "../../assets/paralax/planet.png", { -2.0, 0.0 }, { 10.0, 10.0 }, { 3.0, 4.0 });
        std::shared_ptr<Entity> e3 = createEntity("Background", "../../assets/paralax/planet.png", { -4.0, 0.0 }, { 10.0, 500.0 }, { 3.0, 4.0 });
        std::shared_ptr<Entity> e4 = createEntity("Background", "../../assets/paralax/stars.png", { -3.0, 0.0 }, { -1.0, -1.0 }, { 5.0, 6.0 });
        std::shared_ptr<Entity> e5 = createEntity("Background", "../../assets/paralax/stars.png", { -4.0, 0.0 }, { 0.0, 250.0 }, { 5.0, 6.0 });

        _entities.push_back(std::move(e1));
        _entities.push_back(std::move(e2));
        _entities.push_back(std::move(e3));
        _entities.push_back(std::move(e4));
        _entities.push_back(std::move(e5));

        std::size_t i = 0;

        for (auto entity: _entities) {
            if (i == 15) {
                std::cerr << "Error: upgrade boost::array size" << std::endl;
                break;
            }
            array_buf.at(i) = getInitSpriteData(entity);
            i++;
        }

        if (array_buf[0].id == endArray.id) {
            std::cout << "Error InitECS : Empty array_buf" << std::endl;
            return ;
        }

        Data d = { INITSPRITEDATATYPE, {  }, array_buf };
        boost::array<Data, 1> send_buf = { d };

        for (auto p: _players) {
            // if wrong player, go to next player
            if (p.uuid != uuid) {
                continue;
            }

            // if right player, send buffer
            std::cout << send_buf[0].initSpriteDatas[0].path << std::endl;
            _udp_socket.async_send_to(
                boost::asio::buffer(send_buf),
                p.endpoint,
                boost::bind(
                    &Server::handleSend,
                    this,
                    uuid,
                    send_buf,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
        }
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

SpriteData getSpriteData(std::shared_ptr<Entity> &e) {
    if (!e.get()->has(DRAWABLE)) {
        throw Error("Couldn't find sprite");
    }

    try {
        auto pos = std::dynamic_pointer_cast<Position>(e.get()->getComponent(POSITION));
        auto health = std::dynamic_pointer_cast<Health>(e.get()->getComponent(HEALTH));
        SpriteData s = {
            e.get()->getId(),
            pos.get()->getPos(),
            health.get()->getHp()
        };

        return s;
    } catch (std::exception &e) {
        throw Error(e.what());
    }
}

InitSpriteData Server::getInitSpriteData(std::shared_ptr<Entity> &e) {
    if (!e.get()->has(DRAWABLE)) {
        throw Error("Couldn't find sprite");
    }

    try {
        auto draw = std::dynamic_pointer_cast<Drawable>(e.get()->getComponent(DRAWABLE));
        auto pos = std::dynamic_pointer_cast<Position>(e.get()->getComponent(POSITION));
        auto scale = std::dynamic_pointer_cast<Scale>(e.get()->getComponent(SCALE));
        auto health = std::dynamic_pointer_cast<Health>(e.get()->getComponent(HEALTH));
        InitSpriteData s = {
            e.get()->getId(),              // get the id of the sprite
            draw.get()->getPath(),         // get the path of the texture
            pos.get()->getPos(),           // get the position of the sprite
            scale.get()->getScale(),       // get the scale of the sprite
            draw.get()->getMaxOffset(),    // get the max coordinates of the rect
            health.get()->getHp(),         // get the health
        };

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
