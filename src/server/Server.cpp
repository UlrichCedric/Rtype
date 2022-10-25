/*
** EPITECH PROJECT, 2022
** server
** File description:
** udp boost asio
*/

#include "Server.hpp"

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
    _timer.expires_from_now(boost::posix_time::milliseconds(17));
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
    for (Player player : _players) {
        std::cout << "async send to " << player.uuid << std::endl;
        _socket.async_send_to(
            boost::asio::buffer(send_buf), player.endpoint,
            boost::bind(&Server::handleSend, this, player.uuid,
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
            SpriteData player = {{800, 400}, new_player_info.idSprite};
            _sprites.push_back(player);
        }
        handleInput(_recv_buf[0]);
        // sendSprites();
    }
    startReceive();
}

void Server::handleSend(boost::uuids::uuid uuidReceiver,
    const boost::system::error_code& /*error*/,
    std::size_t /*bytes_transferred*/)
{
    if (_recv_buf.size() > 0) {
        std::cout << "Data sent to " << uuidReceiver << std::endl;
    }
}
