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

void Client::receiveData(boost::array<SpriteData, 16>& recv_buf)
{
    boost::asio::ip::udp::endpoint sender_endpoint;
    size_t len = _socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);
}

boost::uuids::uuid Client::getUuid(void)
{
    return _uuid;
}
