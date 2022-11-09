/*
** EPITECH PROJECT, 2022
** client
** File description:
** udp boost asio
*/

#include "Client.hpp"

void Client::sendData(enum Input action)
{
    boost::array<Action, 1> send_buf = {{action, _uuid}};
    _udp_socket.send_to(boost::asio::buffer(send_buf), _receiver_endpoint);
    std::cout << "sendData" << std::endl;
}

/**
 * @brief ISN'T USED
 *
 * @param action
 */
void Client::asyncSendData(enum Input action)
{
    boost::array<Action, 1> send_buf = {{ action, _uuid }};
    _socket.async_send_to(
        boost::asio::buffer(send_buf),
        _receiver_endpoint,
        boost::bind(
            &Client::handleSendData,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
}

void Client::handleSendData(const boost::system::error_code &error, std::size_t)
{
    std::cout << "handleSendData" << std::endl;
}

/**
 * @brief When client receive data from server
 *
 */
void Client::receiveData(void)
{
    while (_canReceiveData) {
        boost::asio::ip::udp::endpoint sender_endpoint;
        size_t len = _socket.receive_from(
            boost::asio::buffer(
                _recv_buf,
                sizeof(boost::array<Data, 1>)
            ),
            sender_endpoint
        );

        if (len == 0) {
            std::cout << "Received empty data" << std::endl;
            return;
        }
        if (_recv_buf[0].type == INITSPRITEDATATYPE) {
            std::cout << "[1] Received initSpriteData" << std::endl;
            std::cout << "received path: " << _recv_buf[0].initSpriteDatas[0].path << std::endl;
            std::cout << "[2] Received initSpriteData" << std::endl;
            handleInitSpriteData();
        } else if (_recv_buf[0].type == SPRITEDATATYPE) {
            handleSpriteData();
        } else {
            std::cerr << "Undefined type received: please verify what you're sending." << std::endl;
        }
    }
}

/**
 * @brief When client receives intiSpriteData from server
 *
 */
void Client::handleInitSpriteData(void)
{
    for (size_t i = 0; _recv_buf[0].initSpriteDatas[i].id != 0; i++) {

        if (access(_recv_buf[0].initSpriteDatas[i].path, F_OK) != 0) {
            std::cerr << "Path " << _recv_buf[0].initSpriteDatas[i].path << " does not exist" << std::endl;
        }

        std::shared_ptr<Game::Image> img = std::make_shared<Game::Image>(
            _recv_buf[0].initSpriteDatas[i].id,
            _recv_buf[0].initSpriteDatas[i].path,
            _recv_buf[0].initSpriteDatas[i].coords,
            _recv_buf[0].initSpriteDatas[i].scale,
            _recv_buf[0].initSpriteDatas[i].rectSize,
            _recv_buf[0].initSpriteDatas[i].health
        );
        _images.push_back(img);
    }
}

/**
 * @brief When client receives spriteData from server
 *
 */
void Client::handleSpriteData(void)
{
    for (int i = 0; _recv_buf[0].spriteDatas[i].id != 0; i++) {
        for (auto img: _images) {
            if (img.get()->getId() == _recv_buf[0].spriteDatas[i].id) {
                img.get()->setPos(_recv_buf[0].initSpriteDatas[i].coords);
                try {
                    img.get()->setHp(
                        _recv_buf[0].initSpriteDatas[i].health,
                        _recv_buf[0].initSpriteDatas[i].coords
                    );
                } catch (Error &e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
                break;
            }
        }
    }
}

/**
 * @brief DO NOT WORK IN ASYNC
 *
 */
void Client::asyncReceiveData(void)
{
    std::cout << "Async receive Data" << std::endl;
    boost::asio::ip::udp::endpoint sender_endpoint;
    _socket.async_receive_from(
        boost::asio::buffer(_recv_buf),
        sender_endpoint,
        boost::bind(
            &Client::handleReceiveData,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
}

void Client::handleReceiveData(const boost::system::error_code& error, std::size_t /*bytes_transferred*/)
{
    std::cout << "handleReceiveData" << std::endl;
    for (int i = 0; _recv_buf[0].initSpriteDatas[i].id != 0; i++) {
        std::cout << "x: " << _recv_buf[0].initSpriteDatas[i].coords.first << " / y: " << _recv_buf[0].initSpriteDatas[i].coords.second << std::endl;
        _player_pos.first = _recv_buf[0].initSpriteDatas[i].coords.first;
        _player_pos.second = _recv_buf[0].initSpriteDatas[i].coords.second;
    }
    asyncReceiveData();
    // boost::receive_from(
    //     boost::asio::buffer(_recv_buf),
    //     sender_point,
    //     boost::bind(
    //         &Client::handleReceiveData,
    //         this,
    //         boost::asio::placeholders::error,
    //         boost::asio::placeholders::bytes_transferred
    //     )
    // );
}

/**
 * @brief Get the client uuid
 *
 * @return boost::uuids::uuid client's uuid
 */
boost::uuids::uuid Client::getUuid(void)
{
    return _uuid;
}

/**
 * @brief returns the player position
 *
 * @return std::pair<float, float> player position
 */
std::pair<float, float> Client::getPlayerPos(void)
{
    return _player_pos;
}

void Client::handleThread(void)
{
    sendData(NONE);
    receiveData();
}

/**
 * @brief Sets if the client can receive data
 *
 * @param canReceiveData new state as bool value
 */
void Client::setCanReceiveData(bool newState)
{
    _canReceiveData = newState;
}

void Client::createLobby(std::string name, std::size_t size)
{
    Lobby lobby;
    lobby.player_uuid = _uuid;
    lobby.create = true;
    lobby.join = false;
    lobby.name = name;
    lobby.nb_players = 0;
    lobby.size = size;
    lobby.lobby_uuid = boost::uuids::random_generator()();
    lobby.status = OPEN;
    boost::array<Lobby, 1> buffer = {lobby};
    // _tcp_socket.send_to(boost::asio::buffer(buffer), _receiver_endpoint);
    std::cout << "send create Lobby" << std::endl;
}

void Client::joinLobby(boost::uuids::uuid uuid)
{
    Lobby lobby;
    lobby.player_uuid = _uuid;
    lobby.create = false;
    lobby.join = true;
    lobby.name = "";
    lobby.nb_players = 0;
    lobby.size = 0;
    lobby.lobby_uuid = uuid;
    lobby.status = OPEN;
    boost::array<Lobby, 1> buffer = {lobby};
    // _tcp_socket.send_to(boost::asio::buffer(buffer), _receiver_endpoint);
    std::cout << "send join Lobby" << std::endl;
}

std::vector<Lobby> Client::getLobbies(void)
{
    boost::array<Lobby, 16> recv_lobbies;
    boost::asio::ip::tcp::endpoint sender_endpoint;
    // size_t len = _tcp_socket.receive_from(boost::asio::buffer(lobbies, sizeof(boost::array<Lobby, 16>)), sender_endpoint);
    // if (len == 0) {
    //     return;
    // }
    std::vector<Lobby> lobbies;
    for (size_t i = 0; recv_lobbies[i].size != 0; i++) {
        lobbies.push_back(recv_lobbies[i]);
    }
    return lobbies;
}

void Client::writeData(void)
{
    Lobby lobby1 = {_uuid, true, true, "lobby1", 2, 4, boost::uuids::random_generator()(), OPEN};
    Lobby lobby2 = {_uuid, true, true, "lobby2", 2, 4, boost::uuids::random_generator()(), OPEN};
    Lobby lobby3 = {_uuid, true, true, "lobby3", 2, 4, boost::uuids::random_generator()(), OPEN};
    Lobby endArray = {_uuid, false, false, "", 0, 0, boost::uuids::random_generator()(), CLOSE};
    boost::array<Lobby, 16> array_buf;
    array_buf[0] = lobby1;
    array_buf[1] = lobby2;
    array_buf[2] = lobby3;
    array_buf[3] = endArray;
    Data data = {LobbyType, {}, {}, array_buf};
    boost::array<Data, 1> send_buf = {data};
    boost::system::error_code error;
    // probablement possible d'envoyer array_buf direct au lieu de send_buf
    boost::asio::write(_tcp_socket, boost::asio::buffer(send_buf), error);
    if (!error) {
        std::cout << "Client sent data!" << std::endl;
    } else {
        std::cout << "send failed: " << error.message() << std::endl;
    }
}

void Client::readData(void)
{
    boost::system::error_code error;
    boost::asio::read(_tcp_socket, boost::asio::buffer(_recv_buf), error);
    if (!error) {
        if (_recv_buf[0].type == LobbyType) {
            for (int i = 0; _recv_buf[0].lobbies[i].size != 0; i++) {
                std::cout << "Lobby of uuid: " << _recv_buf[0].lobbies[i].lobby_uuid << std::endl;
            }
        }
    } else {
        std::cout << "receive failed: " << error.message() << std::endl;
        return;
    }
}
