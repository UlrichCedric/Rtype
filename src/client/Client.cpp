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

void Client::asyncSendData(enum Input action)
{
    boost::array<Action, 1> send_buf = {{action, _uuid}};
    _udp_socket.async_send_to(
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
    while (_canReceiveData) {
        boost::asio::ip::udp::endpoint sender_endpoint;
        std::string type = "undefined";
        size_t len = _udp_socket.receive_from(boost::asio::buffer(_recv_buf, sizeof(boost::array<Data, 1>)), sender_endpoint);
        if (_recv_buf.size() == 0) {
            continue;
        }
        if (_recv_buf[0].type == InitSpriteDataType) {
            type = "InitSpriteData";
            handleInitSpriteData();
        } else if (_recv_buf[0].type == SpriteDataType) {
            type = "SpriteData";
            handleSpriteData();
        }
        std::cout << type << " data received" << std::endl;
    }
}

void Client::handleInitSpriteData(void)
{
    InitSpriteData endArray = { 0, "", { 0, 0 }, { 0, 0 }, { 0, 0 } };

    for (size_t i = 0;; i++) {
        if (_recv_buf[0].initSpriteDatas[i] == endArray) {
            break;
        }
        _images.push_back(Game::Image(
            _recv_buf[0].initSpriteDatas[i].id,
            _recv_buf[0].initSpriteDatas[i].path,
            _recv_buf[0].initSpriteDatas[i].coords,
            _recv_buf[0].initSpriteDatas[i].scale,
            _recv_buf[0].initSpriteDatas[i].maxSize,
            _recv_buf[0].initSpriteDatas[i].health
        ));
    }
}

void Client::handleSpriteData(void)
{
    // for (int i = 0; _recv_buf[0].spriteDatas[i].id != 0; i++) {
    //     _player_pos.first = _recv_buf[0].spriteDatas[i].coords.first;
    //     _player_pos.second = _recv_buf[0].spriteDatas[i].coords.second;
    // }
    for (int i = 0; _recv_buf[0].spriteDatas[i].id != 0; i++) {
        for (auto img: _images) {
            if (img.getId() == _recv_buf[0].spriteDatas[i].id) {
                img.setPos(_recv_buf[0].initSpriteDatas[i].coords);
                try {
                    img.setHp(
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
    _udp_socket.async_receive_from(boost::asio::buffer(_recv_buf), sender_endpoint,
        boost::bind(&Client::handleReceiveData, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void Client::handleReceiveData(const boost::system::error_code& error, std::size_t /*bytes_transferred*/)
{
    std::cout << "handleReceiveData" << std::endl;
    // for (int i = 0; _recv_buf[i].id != 0; i++) {
    //     std::cout << "x: " << _recv_buf[i].coords.first << " / y: " << _recv_buf[i].coords.second << std::endl;
    //     _player_pos.first = _recv_buf[i].coords.first;
    //     _player_pos.second = _recv_buf[i].coords.second;
    // }
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
}

void Client::setCanReceiveData(bool canReceiveData)
{
    _canReceiveData = canReceiveData;
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
