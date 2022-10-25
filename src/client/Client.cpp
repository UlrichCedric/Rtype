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
    std::cout << "receive Data" << std::endl;
    boost::asio::ip::udp::endpoint sender_endpoint;
    size_t len = _socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);
}

void Client::asyncReceiveData(void)
{
    std::cout << "Async receive Data" << std::endl;
    boost::asio::ip::udp::endpoint sender_endpoint;
    _socket.async_receive_from(boost::asio::buffer(_recv_buf), sender_endpoint,
        boost::bind(&Client::handleReceiveData, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void Client::handleReceiveData(const boost::system::error_code& error, std::size_t /*bytes_transferred*/)
{
    std::cout << "handleReceiveData" << std::endl;
    for (int i = 0; _recv_buf[i].id != 0; i++) {
        std::cout << "id: " <<
            _recv_buf[i].id << "\t-> x: " <<
            _recv_buf[i].coords.first << "\t y: "<<
            _recv_buf[i].coords.second << std::endl;
    }
    asyncReceiveData();
}

boost::uuids::uuid Client::getUuid(void)
{
    return _uuid;
}
