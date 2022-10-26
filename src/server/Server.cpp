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
    _d->run(_entities);
    _h->run(_entities);
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
    for (SpriteData& sprite : _sprites) {
        if (sprite.id == id_sprite_player) {
            moveSprite(sprite, action.input);
        }
    }
}

size_t Server::getEntityIdByUuid(Action action)
{
    std::size_t id_sprite_player = 0;
    Uuid *u;

    for (std::shared_ptr<Entity> ptr: _entities) {
        if (!ptr.get()->has(UUID)) {
            continue;
        }
        u = static_cast<Uuid *>(ptr.get()->getComponent(UUID).get());
        if (u->getUuid() == boost::uuids::to_string(action.uuid)) {
            return ptr.get()->getId();
        }
    }
    return -1;
}

void Server::handleInput(Action action)
{
    size_t id = getEntityIdByUuid(action);

    if (action.input != NONE) {
        if (id == -1) {
            return;
        }
        if (action.input == SPACE) {
            /* shoot projectile */
            return;
        }
        Entity *ptr = static_cast<Entity *>(_f.get()->getEntityById(id).get());
        Velocity *vel = static_cast<Velocity *>(ptr->getComponent("velocity").get());

        if (vel == nullptr) {
            return;
        }

        switch (action.input) {
            case (UP): vel->setYVelocity(1); break;
            case (DOWN): vel->setYVelocity(-1); break;
            case (LEFT): vel->setXVelocity(-1); break;
            case (RIGHT): vel->setXVelocity(1); break;
            default: break;
        }
    }
}

void Server::sendSprites(void)
{
    SpriteData endArray = {0, {0, 0}};
    boost::array<SpriteData, 16> send_buf = {endArray};
    for (int i = 0; i <= _sprites.size(); i++) {
        if (i == 15) {
            /*
                Provisoire, c'est au cas où il y ait + que 16 sprites, pour éviter le crash
            */
            std::cout << "/!\\ Agrandir la boost::array SpriteData /!\\" << std::endl;
            send_buf[i] = endArray;
            break;
        }
        if (i == _sprites.size()) {
            send_buf[i] = endArray;
        } else {
            send_buf[i] = _sprites[i];
        }
    }
    _socket.async_send_to(
        boost::asio::buffer(send_buf), _remote_endpoint,
        boost::bind(&Server::handleSend, this, send_buf,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

void Server::handleReceive(const boost::system::error_code& error, std::size_t /*bytes_transferred*/)
{
    if (!error) {
        std::cout << "Received: " << _recv_buf[0].input << " from " << _recv_buf[0].uuid << std::endl;
        if (isNewUuid(_recv_buf[0].uuid)) {
            std::cout << "New player !" << std::endl;
            std::pair<boost::uuids::uuid, std::size_t> new_player_info = {_recv_buf[0].uuid, setNewSpriteId(0)};
            _players_uuid.push_back(new_player_info);
            SpriteData player = {new_player_info.second, {800, 400}};
            _sprites.push_back(player);
        }
        handleInput(_recv_buf[0]);
        sendSprites();
    }
    startReceive();
}

void Server::handleSend(boost::array<SpriteData, 16> /*data*/,
        const boost::system::error_code& /*error*/,
        std::size_t /*bytes_transferred*/)
{
    if (_recv_buf.size() > 0) {
        std::cout << "Data sent to " << _recv_buf[0].uuid << std::endl;
    }
}
