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
    _socket.send_to(boost::asio::buffer(send_buf), _receiver_endpoint);
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

void Client::handleSendData(const boost::system::error_code& error, std::size_t /*bytes_transferred*/)
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
            std::cout << _recv_buf[0].initSpriteDatas[0].path << std::endl;
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
    InitSpriteData endArray = { 0, "", { 0, 0 }, { 0, 0 }, { 0, 0 } };

    for (size_t i = 0; _recv_buf[0].initSpriteDatas[i].id != endArray.id ; i++) {
        std::cout << "le path de le image: " << _recv_buf[0].initSpriteDatas[i].path << std::endl;
        std::shared_ptr<Game::Image> img = std::make_shared<Game::Image>(
            _recv_buf[0].initSpriteDatas[i].id,
            _recv_buf[0].initSpriteDatas[i].path,
            _recv_buf[0].initSpriteDatas[i].coords,
            _recv_buf[0].initSpriteDatas[i].scale,
            _recv_buf[0].initSpriteDatas[i].maxSize,
            _recv_buf[0].initSpriteDatas[i].health
        );
        _images.push_back(std::move(img));
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
