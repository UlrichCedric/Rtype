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
}

void Client::asyncSendData(enum Input action)
{
    boost::array<Action, 1> send_buf = {{action, _uuid}};
    _socket.async_send_to(
        boost::asio::buffer(send_buf), _receiver_endpoint,
        boost::bind(&Client::handleSendData, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void Client::handleSendData(const boost::system::error_code& error, std::size_t /*bytes_transferred*/)
{
    std::cout << "sendData" << std::endl;
}

void Client::receiveData(void)
{
    boost::array<SpriteData, 16> recv_buf;
    std::cout << "receive Data" << std::endl;
    boost::asio::ip::udp::endpoint sender_endpoint;
    size_t len = _socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);
    for (int i = 0; recv_buf[i].id != 0; i++) {
        _player_pos.first = recv_buf[i].coords.first;
        _player_pos.second = recv_buf[i].coords.second;
    }
}

void Client::asyncReceiveData(void)
{
    boost::array<SpriteData, 16> recv_buf;
    std::cout << "Async receive Data" << std::endl;
    boost::asio::ip::udp::endpoint sender_endpoint;
    _socket.async_receive_from(boost::asio::buffer(recv_buf), sender_endpoint,
        boost::bind(&Client::handleReceiveData, this, recv_buf,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void Client::handleReceiveData(boost::array<SpriteData, 16> recv_buf,
    const boost::system::error_code& error, std::size_t /*bytes_transferred*/)
{
    std::cout << "handleReceiveData" << std::endl;
    for (int i = 0; recv_buf[i].id != 0; i++) {
        std::cout << "x: " << recv_buf[i].coords.first << " / y: " << recv_buf[i].coords.second << std::endl;
        _player_pos.first = recv_buf[i].coords.first;
        _player_pos.second = recv_buf[i].coords.second;
    }
    asyncReceiveData();
}

boost::uuids::uuid Client::getUuid(void)
{
    return _uuid;
}

std::pair<float, float> Client::getPlayerPos(void)
{
    return _player_pos;
}
