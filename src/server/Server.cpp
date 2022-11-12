/*
** EPITECH PROJECT, 2022
** server
** File description:
** udp boost asio
*/

#include "Server.hpp"
#include "ecs/constants.hpp"

/**
 * @brief parses the 'enemies.conf' file to get the different waves
 *
 */
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
        std::string name = "./assets/sprites/" + string.substr(string.find(':', 0) + 1, string.length() - 1);
        _waveConf[i++] = std::pair<std::size_t, std::string>(number, name);
    }
}

/** @brief start receiving upd
 *
 */
void Server::startReceive(void)
{
    _udp_socket.async_receive_from(
        boost::asio::buffer(_recv_buf),
        _remote_endpoint,
        boost::bind(
            &Server::handleReceive,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
}

/**
 * @brief server gameloop
 *
 */
void Server::handleTimer(void) {
    // Wait for next timeout.
    _d->run(_entities);
    _h->run(_entities);
    _hit->run(_entities);
    sendSprites();
    _timer.expires_from_now(boost::posix_time::milliseconds(10));
    _timer.async_wait(boost::bind(&Server::handleTimer, this));
}

/**
 * @brief Returns true if the given UUID is not already on the server
 *
 * @param uuid of the client
 * @return true if the given client is a new one
 * @return false if the client is already on the server
 */
bool Server::isNewUuid(boost::uuids::uuid uuid)
{
    std::vector<boost::uuids::uuid> uuids;

    for (Player player : _players) {
        uuids.push_back(player.uuid);
    }
    return (std::find(uuids.begin(), uuids.end(), _recv_buf[0].uuid) == uuids.end());
}

/**
 * @brief Returns the next available id
 *
 * @param new_id just send it a 0, it will work recursively
 * @return std::size_t returns the new available id
 */
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

void Server::moveSprite(std::shared_ptr<Velocity> vel, enum Input input)
{
    switch (input) {
        case UP: vel->setYVelocity(-4); vel->setXVelocity(0); break;
        case DOWN: vel->setYVelocity(4); vel->setXVelocity(0); break;
        case LEFT: vel->setXVelocity(-4); vel->setYVelocity(0); break;
        case RIGHT:vel->setXVelocity(4); vel->setYVelocity(0); break;
        default: vel->setYVelocity(0); vel->setXVelocity(0); break;
    }
}

/** @brief gets the sprite from the given player
 *
 * @param acttion { uuid of the player, action (not used) }
 */
void Server::findPlayerSprite(Action action)
{
    for (auto entity: _entities) {
        if (!entity->has(VELOCITY) || !entity->has(UUID) ) {
            continue;
        }

        auto uuid = std::dynamic_pointer_cast<Uuid>(entity->getComponent(UUID));

        if (entity->getId() == getEntityIdByUuid(action)) {
            auto vel = std::dynamic_pointer_cast<Velocity>(entity->getComponent(VELOCITY));
            moveSprite(vel, action.input);
        }
    }
}

/** @brief handle any input sent from client UDP
 *
 * @param action sent from the client { uuid, key_pressed }
 *
 */
void Server::handleInput(Action action)
{
    switch (action.input) {
        case (SPACE): std::cout << "shoot" << std::endl; break;
        default: findPlayerSprite(action); break;
    }
}

/**
 * @brief Sending sprites
 *
 */
void Server::sendSprites(void)
{
    SpriteData endArray = { 0, { 0.0, 0.0 }, 0 };
    boost::array<SpriteData, 128> array_buf = { endArray };
    std::size_t i = 0;

    for (auto entity: _entities) {
        if (i == 128) {
            /*
                Provisoire, c'est au cas où il y ait + que 16 sprites, pour éviter le crash
            */
            std::cout << "/!\\ Agrandir la boost::array SpriteData /!\\" << std::endl;
            array_buf[i] = endArray;
            break;
        }
        array_buf[i++] = getSpriteData(entity);
    }
    array_buf[i] = endArray;

    Data data = { SPRITEDATATYPE, array_buf, { }, { } };
    boost::array<Data, 1> send_buf = { data };

    for (Player player : _players) {
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
 * @brief When received a UDP message from the client
 *
 * @param error if any
 * @param std::size_t byte size
 */
void Server::handleReceive(const boost::system::error_code &error, std::size_t bytes)
{
    if (error || bytes == 0) {
        return;
    }
    if (isNewUuid(_recv_buf[0].uuid)) {
        std::cout << "New player with UUID: " << _recv_buf[0].uuid << std::endl;

        Player new_player = {
            .endpoint = _remote_endpoint,
            .uuid = _recv_buf[0].uuid,
            .idSprite = setNewSpriteId(0)
        };

        _players.push_back(new_player);

        SpriteData player = { new_player.idSprite, { 800.0, 400.0 }, 100 };
        std::cout << "init ecs !!" << std::endl;
        initEcs(_recv_buf[0].uuid, new_player.idSprite);
    }
    handleInput(_recv_buf[0]);
    startReceive();
}

/**
 * @brief brief verifying what you're sending to the client
 *
 * @param boost::uuids::uuid uuid of the client
 * @param const boost::array<Data, 1> data sent to the client
 * @param const boost::system::error_code& error code
 * @param std::size_t number of bytes received
 */
void Server::handleSend(
    boost::uuids::uuid uuidReceiver,
    const boost::array<Data, 1> send_buf,
    const boost::system::error_code &,
    std::size_t
) {
    if (send_buf[0].type == INITSPRITEDATATYPE && send_buf[0].initSpriteDatas[0].id == 0) {
        std::cerr << "Empty initSpriteData buffer sent" << std::endl;
        return;
    }
    if (send_buf[0].type == SPRITEDATATYPE && send_buf[0].spriteDatas[0].id == 0) {
        std::cerr << "Empty spriteData buffer sent" << std::endl;
        return;
    }


    InitSpriteData endArray = { 0, "", { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, 0 };

    // If you wanna display what you're sending to the client
    ////////////////////////////////////////////////////////////////
    // if (send_buf[0].type == INITSPRITEDATATYPE) {
    //     for (size_t i = 0; send_buf[0].initSpriteDatas[i].id != endArray.id ; i++) {
    //         std::cout << "inside handleSend -> path: " << send_buf[0].initSpriteDatas[i].path << std::endl;
    //     }
    // } else if (send_buf[0].type == SPRITEDATATYPE) {
    //     std::cout << "SpriteData sent: " << send_buf[0].spriteDatas[0].coords.first << std::endl;
    // }
    ////////////////////////////////////////////////////////////////
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
    boost::asio::async_read(
        *(socket.get()),
        boost::asio::buffer(_lobby_buf),
        boost::bind(
            &Server::handleRead,
            this,
            socket,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
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

void Server::handleRead(
    std::shared_ptr<boost::asio::ip::tcp::socket> socket,
    boost::system::error_code const& error,
    size_t bytes_transferred
) {
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
        if (_lobby_buf[0].type == LOBBYTYPE) {
            std::size_t j = findIndexFromSocket(socket);
            if (j != -1) {
                _sockets[j].first = _lobby_buf[0].lobbies[0].player_uuid;
            }
            for (int i = 0; _lobby_buf[0].lobbies[i].size != 0; i++) {
                std::cout << "Lobby of uuid: " << _lobby_buf[0].lobbies[i].lobby_uuid
                << "from user " << _lobby_buf[0].lobbies[i].player_uuid << std::endl;
            }
        }
        std::cout << "List of players uuid paired with socket: " << std::endl;
        std::size_t socket_index = 0;
        for (auto pair : _sockets) {
            std::cout << socket_index << ": " << pair.first << std::endl;
            socket_index += 1;
        }
        asyncRead(socket);
    }
}

void Server::send(void)
{
    Lobby lobby1 = { boost::uuids::random_generator()(), true, true, "lobby1", 2, 4, boost::uuids::random_generator()(), OPEN };
    Lobby lobby2 = { boost::uuids::random_generator()(), true, true, "lobby2", 2, 4, boost::uuids::random_generator()(), OPEN };
    Lobby lobby3 = { boost::uuids::random_generator()(), true, true, "lobby3", 2, 4, boost::uuids::random_generator()(), OPEN };
    Lobby endArray = { boost::uuids::random_generator()(), false, false, "", 0, 0, boost::uuids::random_generator()(), CLOSE };
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

/**
 * @brief create a new entity with the given parameters
 *
 * @param template of the new entity
 * @param path of the texture
 * @param velocity if any
 * @param position of the new sprite
 * @param scale of the new sprite
 * @return std::shared_ptr<Entity> new sprite
 */
std::shared_ptr<Entity> Server::createEntity(
    std::string templ,
    std::string path,
    std::pair<float, float> velocity,
    std::pair<float, float> position = { -1.0, -1.0 },
    std::pair<float, float> scale = { 1.0, 1.0 },
    std::pair<float, float> rect = { 10.0, 10.0 },
    std::string uuid = "EMPTY",
    std::size_t id = 0
) {
    std::shared_ptr<Entity> e;
    if (id != 0) {
        e = _f->createEntity(templ, id);
    } else {
        e = _f->createEntity(templ);
    }

    try {
        if (e->has(DRAWABLE) && !path.empty()) {
            auto eDraw = std::dynamic_pointer_cast<Drawable>(e->getComponent(DRAWABLE));
            eDraw->setSprite(path);
            eDraw->setRectSize(rect);
        }
        if (e->has(VELOCITY)) {
            auto eVel = std::dynamic_pointer_cast<Velocity>(e->getComponent(VELOCITY));
            eVel->setXVelocity(velocity.first);
            eVel->setYVelocity(velocity.second);
        }
        if (e->has(SCALE)) {
            auto eScale = std::dynamic_pointer_cast<Scale>(e->getComponent(SCALE));
            eScale->setXScale(scale.first);
            eScale->setYScale(scale.second);
        }
        if (e->has(POSITION) && position.first != -1 && position.second != -1) {
            auto ePos = std::dynamic_pointer_cast<Position>(e->getComponent(POSITION));
            ePos->setXPos(position.first);
            ePos->setYPos(position.second);
        }

        if (e->has(HITBOX)) {
            auto eHit = std::dynamic_pointer_cast<Hitbox>(e->getComponent(HITBOX));
            eHit->setPos(position);
            eHit->setSize(rect);
        }

        if (uuid != "EMPTY" && e->has(UUID)) {
            auto eUuid = std::dynamic_pointer_cast<Uuid>(e->getComponent(UUID));
            eUuid->setUuid(uuid);
        }
    } catch (Error &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return e;
}

/**
 * @brief creates the necessary sprites to launch the game
 *
 * @param uuid of the new client
 * @param idSprite sprite ID of the new player
 */
void Server::initEcs(boost::uuids::uuid uuid, std::size_t idSprite)
{
    InitSpriteData endArray = { 0, "", { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, 0 };
    std::string uuid_str = boost::uuids::to_string(uuid);

    try {
        _entities.push_back(createEntity("Player", "./assets/sprites/player.gif", { 0.1, 0.1 }, { 10.0, 10.0 }, { 3.0, 3.0 }, { 33.0, 16.0 }, uuid_str, idSprite));

        std::size_t i = 0;
        boost::array<InitSpriteData, 128> array_buf = { endArray };

        for (auto entity: _entities) {
            if (i == 15) {
                std::cerr << "Error: upgrade boost::array size" << std::endl;
                break;
            }
            array_buf.at(i++) = getInitSpriteData(entity);
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
                    boost::asio::placeholders::bytes_transferred
                )
            );
        }

        if (_players.size() == 1) {
            launchWave(0);
        }
    } catch (Error &e) {
        std::cerr << "Error initECS: " << e.what() << std::endl;
    }
}

/**
 * @brief launch new wave by creating its sprites
 *
 */
void Server::launchWave(std::size_t wave) {
    std::srand(std::time(nullptr));
    _currentWave = wave;
    boost::array<InitSpriteData, 128> array_buf = {  };

    for (std::size_t i = 0; i < _waveConf[wave].first; ++i) {
        std::shared_ptr<Entity> e = createEntity(
            "Enemy",                                            // enemy template
            _waveConf[wave].second,                             // texture path
            {
                static_cast<float>(0),       // velocity X: negative (goes to the player)
                static_cast<float>(0)             // velocity Y: may change during the game
            },
            // { 500.0, static_cast<float>(std::rand() % 700) },   // position (X out of the window, Y between 0 and 700)
            { 10.0 + (float)i, 10.0 + (float)i },
            { 2.0, 2.0 },                                       // scale
            { 33.0, 16.0 }                                      // size of the sprite
        );
        _entities.push_back(e);
        array_buf[i] = getInitSpriteData(e);
    }

    boost::array<Data, 1> send_buf = { INITSPRITEDATATYPE, {}, array_buf, {} };

    for (Player p: _players) {
        _udp_socket.async_send_to(
            boost::asio::buffer(send_buf),
            p.endpoint,
            boost::bind(
                &Server::handleSend,
                this,
                p.uuid,
                send_buf,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred
            )
        );
    }
}

/**
 * @brief returns the SpriteData based on the given entity
 *
 * @param e the entity to get the SpriteData from
 * @return SpriteData from the given entity
 */
SpriteData Server::getSpriteData(std::shared_ptr<Entity> &e) {
    if (!e.get()->has(DRAWABLE)) {
        throw Error("Couldn't find sprite");
    }

    try {
        // std::shared_ptr<Position> pos;
        std::pair<float, float> pos = std::make_pair<float, float>(0.0, 0.0);
        // std::shared_ptr<Health> health;
        int health = -1;


        if (e->has(POSITION)) {
            pos = std::dynamic_pointer_cast<Position>(e->getComponent(POSITION))->getPos();
        }
        if (e->has(HEALTH)) {
            health = std::dynamic_pointer_cast<Health>(e->getComponent(HEALTH))->getHp();
        }

        SpriteData s = {
            .id = e->getId(),
            .coords = pos,
            .health = health
        };

        return s;
    } catch (Error &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

/**
 * @brief returns the InitSpriteData based on the given entity
 *
 * @param e the entity to get the InitSpriteData from
 * @return InitSpriteData from the given entity
 */
InitSpriteData Server::getInitSpriteData(std::shared_ptr<Entity> &e) {
    if (!e.get()->has(DRAWABLE)) {
        throw Error("Couldn't find sprite");
    }

    try {
        auto draw = std::dynamic_pointer_cast<Drawable>(e->getComponent(DRAWABLE));
        auto pos = std::dynamic_pointer_cast<Position>(e->getComponent(POSITION));
        auto scale = std::dynamic_pointer_cast<Scale>(e->getComponent(SCALE));
        std::shared_ptr<Health> health;
        if (e->has(HEALTH)) {
            health = std::dynamic_pointer_cast<Health>(e->getComponent(HEALTH));
        }
        InitSpriteData s = {
            .id = e->getId(),                                     // get the id of the sprite
            .coords = pos->getPos(),                              // get the position of the sprite
            .scale = scale->getScale(),                           // get the scale of the sprite
            .rectSize = draw->getRectSize(),                      // get the max coordinates of the rect
            .health = e->has(HEALTH) ? health->getHp() : -1       // get the health
        };
        strcpy(s.path, draw->getPath().c_str());

        return s;
    } catch (std::exception &e) {
        std::cerr << "Error - getInitSpriteData: " << e.what() << std::endl;
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
        if (!entity->has(UUID)) {
            continue;
        }
        try {
            u = std::dynamic_pointer_cast<Uuid>(entity->getComponent(UUID));
        } catch (std::exception &e) {
            /*
                For any reason, if the first verification failed, and this entity
                still doesn't have any UUID, just continue to the next one
            */
            continue;
        }

        if (u->getUuid() == boost::uuids::to_string(action.uuid)) {
            return entity->getId();
        }
    }
    throw Error("Entity not found");
}
