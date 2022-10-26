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
    std::cout << "handleSendData" << std::endl;
}

void Client::receiveData(void)
{
    boost::array<SpriteData, 16> recv_buf;
    std::cout << "receive Data" << std::endl;
    boost::asio::ip::udp::endpoint sender_endpoint;
    if (_canReceiveData) {
        size_t len = _socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);
        for (int i = 0; recv_buf[i].id != 0; i++) {
            _player_pos.first = recv_buf[i].coords.first;
            _player_pos.second = recv_buf[i].coords.second;
        }
        receiveData();
    }
}

/**
 * Le problème de ne pas recevoir de Data quand on est en async vient très probablement du
 * boost::bind car lorsque j'envoie des données en async avec async_send_to, mon serveur
 * reçoit bien des données, cependant la fonction "handleSendData" du boost::bind n'est
 * pas appelé (std::cout << "handleSendData" << std::endl; n'est pas affiché).
 *
 * Etant donné que la gestion des données reçues lors de async_receive_from est géré
 * dans handleReceiveData lui même étant dans boost::bind, handleReceiveData n'est
 * jamais appelé, les données ne sont donc jamais traitées.
 * Pour l'instant résolu avec un système de thread + appel en continu de receiveData dans
 * le thread (c'est donc à part, non bloquant pour le jeu).
 * Autre possibilité de résolution : Etant donné qu'il est très probable que je reçoive
 * bien de la data grâce à async_receive_from et donc que recv_buf est update,
 * mettre _recv_buf comme attribut et update les données en continu grâce à _recv_buf.
 *
 * UPDATE -> en fait ça met pas à jour _recv_buf donc faire un thread à part qui
 * appelle receiveData en boucle est la meilleure solution.
*/
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
        std::cout << "x: " << _recv_buf[i].coords.first << " / y: " << _recv_buf[i].coords.second << std::endl;
        _player_pos.first = _recv_buf[i].coords.first;
        _player_pos.second = _recv_buf[i].coords.second;
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

void Client::handleThread(void)
{
    sendData(NONE);
    receiveData();
    std::cout << "io_context.run()" << std::endl;
    _io_context.run();
}

void Client::setCanReceiveData(bool canReceiveData)
{
    _canReceiveData = canReceiveData;
}
