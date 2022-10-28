/*
** EPITECH PROJECT, 2022
** server
** File description:
** udp boost asio
*/

#include "Server.hpp"

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

    std::size_t i = 0;
    InitSpriteData emptyInitBuffer = { 0, "", { 0, 0 }, { 0, 0 }, { 0, 0 } };
    boost::array<InitSpriteData, 16> buffer = { emptyInitBuffer }; // Initialize send_buf to empty array

    std::shared_ptr<Entity> e1;
    std::shared_ptr<Entity> e2;
    std::shared_ptr<Entity> e3;
    std::shared_ptr<Entity> e4;
    std::shared_ptr<Entity> e5;

    try {
        e1 = createEntity("Background", "../../assets/paralax/back.png", { -1.0, 0.0 }, { -1.0, -1.0 }, { 5.0, 6.0 });

        e2 = createEntity("Background", "../../assets/paralax/planet.png", { -2.0, 0.0 }, { 10.0, 10.0 }, { 3.0, 4.0 });

        e3 = createEntity("Background", "../../assets/paralax/planet.png", { -4.0, 0.0 }, { 10.0, 500.0 }, { 3.0, 4.0 });
        e4 = createEntity("Background", "../../assets/paralax/stars.png", { -3.0, 0.0 }, { -1.0, -1.0 }, { 5.0, 6.0 });
        e5 = createEntity("Background", "../../assets/paralax/stars.png", { -4.0, 0.0 }, { 0.0, 250.0 }, { 5.0, 6.0 });

        _entities.push_back(std::move(e1));
        _entities.push_back(std::move(e2));
        _entities.push_back(std::move(e3));
        _entities.push_back(std::move(e4));
        _entities.push_back(std::move(e5));

        for (auto entity: _entities) {
            buffer[i] = getInitSpriteData(entity);
        }
        _socket.async_send_to(
            boost::asio::buffer(buffer),
            _remote_endpoint,
            boost::bind(
                &Server::handleSend,
                this,
                buffer,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred
            )
        );
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Server::startReceive(void)
{
    _socket.async_receive_from(
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

void Server::handleTimer(void)
{
    _d->run(_entities);
    _h->run(_entities);

    _timer.expires_from_now(boost::posix_time::milliseconds(10));
    _timer.async_wait(boost::bind(&Server::handleTimer, this));
}

bool Server::isNewUuid(boost::uuids::uuid uuid)
{
    std::vector<boost::uuids::uuid> uuids;

    for (std::pair<boost::uuids::uuid, std::size_t> player : _players_uuid) {
        uuids.push_back(player.first);
    }
    return std::find(uuids.begin(), uuids.end(), _recv_buf[0].uuid) == uuids.end();
}

void Server::findPlayerSprite(Action action)
{
    std::size_t id_sprite_player = 0;

    for (std::pair<boost::uuids::uuid, std::size_t>& player : _players_uuid) {
        if (action.uuid == player.first) {
            id_sprite_player = player.second;
            break;
        }
    }
    if (id_sprite_player == 0) {
        return;
    }
    for (auto entity: _entities) {
        if (entity.get()->getId() == id_sprite_player) {
            _d->run(_entities);
            _h->run(_entities);
        }
    }
    // _sprites is deprecated
    //
    // for (SpriteData& sprite : _sprites) {
    //     if (sprite.id == id_sprite_player) {
    //         moveSprite(sprite, action.input);
    //     }
    // }
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

void Server::handleInput(Action action)
{
    std::size_t id = getEntityIdByUuid(action);

    if (action.input != NONE) {
        if (id == -1) {
            return;
        }
        if (action.input == SPACE) {
            /* shoot projectile */
            return;
        }

        try {
            auto entity = dynamic_pointer_cast<Entity>(_f.get()->getEntityById(id));
            auto vel = dynamic_pointer_cast<Velocity>(entity->getComponent(VELOCITY));

            switch (action.input) {
                case (UP): vel->setYVelocity(1); break;
                case (DOWN): vel->setYVelocity(-1); break;
                case (LEFT): vel->setXVelocity(-1); break;
                case (RIGHT): vel->setXVelocity(1); break;
                default: break;
            }
        } catch (Error &e) {
            std::cerr << "Error : " << e.what() << std::endl;
        }
    }
}

void Server::sendSprites(void)
{
    SpriteData endArray = {0, {0, 0}};
    boost::array<SpriteData, 16> send_buf = { endArray };
    for (int i = 0; i <= _entities.size(); i++) {
        /*
            Provisoire, c'est au cas où il y ait + que 16 sprites, pour éviter le crash
        */
        if (i == 15) {
            std::cerr << "/!\\ Agrandir la boost::array SpriteData /!\\" << std::endl;
            send_buf[i] = endArray;
            break;
        }
        if (i == _entities.size()) {
            send_buf[i] = endArray;
            continue;
        }
        send_buf[i] = getPositionUpdate(_entities[i]);
    }
    _socket.async_send_to(
        boost::asio::buffer(send_buf), _remote_endpoint,
        boost::bind(&Server::handleSend, this, send_buf,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

/**
 * @brief when data received
 *
 * @param error if error
 * @param bytes size received
 */
void Server::handleReceive(const boost::system::error_code &error, std::size_t bytes)
{
    if (!error) {
        std::cerr << "Server::handleReceive failed" << std::endl;
        return;
    }
    std::cout << "Received: " << _recv_buf[0].input << " from " << _recv_buf[0].uuid << std::endl;
    if (isNewUuid(_recv_buf[0].uuid)) {
        std::cout << "New player !" << std::endl;
        std::size_t id = _f.get()->getAvailableId();
        std::shared_ptr<Entity> e = _f.get()->createEntity("Player", id);
        std::pair<boost::uuids::uuid, std::size_t> new_player_info = { _recv_buf[0].uuid, id };
        _players_uuid.push_back(new_player_info);
        // SpriteData player = { new_player_info.second, { 800, 400 } };
        InitSpriteData player = { getInitSpriteData(e) };
        // _sprites.push_back(player); // _sprites is deprecated
    }
    handleInput(_recv_buf[0]);
    sendSprites();
    startReceive();
}

void Server::handleSend(
    boost::array<SpriteData, 16> /*data*/,
    const boost::system::error_code& /*error*/,
    std::size_t /*bytes_transferred*/
) {
    if (_recv_buf.size() > 0) {
        std::cout << "Data sent to " << _recv_buf[0].uuid << std::endl;
    }
}

SpriteData getPositionUpdate(std::shared_ptr<Entity> &e) {
    if (!e.get()->has(DRAWABLE)) {
        throw Error("Couldn't find sprite");
    }
    std::size_t id = e.get()->getId();
    auto pos = std::dynamic_pointer_cast<Position>(e.get()->getComponent(POSITION));
    SpriteData s = { id, pos->getPos() };

    return s;
}

InitSpriteData getInitSpriteData(std::shared_ptr<Entity> &e) {
    if (!e.get()->has(DRAWABLE)) {
        throw Error("Couldn't find sprite");
    }

    try {
        auto draw = std::dynamic_pointer_cast<Drawable>(e.get()->getComponent(DRAWABLE));
        auto pos = std::dynamic_pointer_cast<Position>(e.get()->getComponent(POSITION));
        auto scale = std::dynamic_pointer_cast<Scale>(e.get()->getComponent(SCALE));
        InitSpriteData s = {
            e.get()->getId(),       // get the id of the sprite
            draw.get()->getPath(),         // get the path of the texture
            pos.get()->getPos(),           // get the position of the sprite
            scale.get()->getScale(),       // get the scale of the sprite
            draw.get()->getMaxOffset()     // get the max coordinates of the rect
        };

        return s;
    } catch (std::exception &e) {
        throw Error(e.what());
    }
}