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
        _waveConf[i++] = std::make_pair<std::size_t, std::string>(number, name);
    }

    std::cout << "Testing parsing on enemies.conf:" << std::endl;
    for (auto [key, value]: _waveConf) {
        std::cout << "For key [" << key << "] = " << value.first << ", " << value.second << std::endl;
    }
    std::cout << "Testing finished" << std::endl;
}

void Server::startReceive(void)
{
    _socket.async_receive_from(
        boost::asio::buffer(_recv_buf), _remote_endpoint,
        boost::bind(&Server::handleReceive, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

void Server::handleTimer(void) {
    std::cout << "handleTimer" << std::endl;
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
    SpriteData endArray = {{0.0, 0.0}, 0};
    boost::array<SpriteData, 16> array_buf = {endArray};
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
        _socket.async_send_to(
            boost::asio::buffer(send_buf), player.endpoint,
            boost::bind(&Server::handleSend, this, player.uuid, send_buf,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }
}

void Server::handleReceive(const boost::system::error_code& error, std::size_t /*bytes_transferred*/)
{
    if (!error) {
        std::cout << "Received: " << _recv_buf[0].input << " from " << _recv_buf[0].uuid << std::endl;
        if (isNewUuid(_recv_buf[0].uuid)) {
            std::cout << "New player !" << std::endl;
            Player new_player_info = {_remote_endpoint, _recv_buf[0].uuid, setNewSpriteId(0)};
            _players.push_back(new_player_info);
            SpriteData player = {{800.0, 400.0}, new_player_info.idSprite};
            _sprites.push_back(player);
        }
        handleInput(_recv_buf[0]);
        // sendSprites();
    }
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
            buffer[i++] = getInitSpriteData(entity);
        }
        buffer[i] = endArray;
        boost::array<SpriteData, 16> empty_array;
        Data data = {InitSpriteDataType, empty_array, buffer};
        boost::array<Data, 1> send_buf = {data};
        for (Player player : _players) {
            std::cout << "async send to " << player.uuid << std::endl;
            _socket.async_send_to(
                boost::asio::buffer(send_buf), player.endpoint,
                boost::bind(&Server::handleSend, this, player.uuid, send_buf,
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
