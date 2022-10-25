/*
** EPITECH PROJECT, 2022
** server
** File description:
** udp boost asio
*/

#include "Server.hpp"

void Server::initEcs(void)
{
    _f = std::make_unique<Factory>();
    _d = std::make_unique<DrawSystem>();
    _h = std::make_unique<HealthSystem>();

    std::shared_ptr<Entity> e1 = std::move(_f.get()->createEntity("Background"));
    if (e1.get() != nullptr) {
        std::cout << "c'est nul" << std::endl;
    }
    static_cast<Drawable *>(e1.get()->getComponent("Drawable").get())->setSprite("../../assets/paralax/back.png");
    // static_cast<Velocity *>(e1.get()->getComponent("Velocity").get())->setXVelocity(-1);
    // static_cast<Scale *>(e1.get()->getComponent("Scale").get())->setScale(5.0, 6.0);

    std::shared_ptr<Entity> e2 = _f.get()->createEntity("Background");
    static_cast<Drawable *>(e2.get()->getComponent("Drawable").get())->setSprite("../../assets/paralax/planet.png");
    // static_cast<Velocity *>(e2.get()->getComponent("Velocity").get())->setXVelocity(-2);
    // static_cast<Position *>(e2.get()->getComponent("Position").get())->setPos(std::make_pair<int, int>(10, 10));
    // static_cast<Scale *>(e2.get()->getComponent("Scale").get())->setScale(3.0, 4.0);

    std::shared_ptr<Entity> e3 = _f.get()->createEntity("Background");
    static_cast<Drawable *>(e3.get()->getComponent("Drawable").get())->setSprite("../../assets/paralax/planet.png");
    // static_cast<Velocity *>(e3.get()->getComponent("Velocity").get())->setXVelocity(-4);
    // static_cast<Position *>(e3.get()->getComponent("Position").get())->setPos(std::make_pair<int, int>(10, 500));
    // static_cast<Scale *>(e3.get()->getComponent("Scale").get())->setScale(3.0, 4.0);

    std::shared_ptr<Entity> e4 = _f.get()->createEntity("Background");
    static_cast<Drawable *>(e4.get()->getComponent("Drawable").get())->setSprite("../../assets/paralax/stars.png");
    // static_cast<Velocity *>(e4.get()->getComponent("Velocity").get())->setXVelocity(-3);
    // static_cast<Scale *>(e4.get()->getComponent("Scale").get())->setScale(5.0, 6.0);

    std::shared_ptr<Entity> e5 = _f.get()->createEntity("Background");
    static_cast<Drawable *>(e5.get()->getComponent("Drawable").get())->setSprite("../../assets/paralax/stars.png");
    // static_cast<Velocity *>(e5.get()->getComponent("Velocity").get())->setXVelocity(-4);
    // static_cast<Position *>(e5.get()->getComponent("Position").get())->setPos(std::make_pair<int, int>(0, 250));
    // static_cast<Scale *>(e5.get()->getComponent("Scale").get())->setScale(5.0, 6.0);

    _entities.push_back(std::move(e1));
    _entities.push_back(std::move(e2));
    _entities.push_back(std::move(e3));
    _entities.push_back(std::move(e4));
    _entities.push_back(std::move(e5));
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
    SpriteData endArray = {{0, 0}, 0};
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
            SpriteData player = {{800, 400}, new_player_info.second};
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
