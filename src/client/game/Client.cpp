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

void Client::createLobby(std::string name)
{
    std::array<char, 64> buf_name;
    for (size_t i = 0;; i++) {
        buf_name[i] = name[i];
        if (name[i] == '\0') {
            break;
        }
    }
    Lobby lobby;
    lobby.player_uuid = _uuid;
    lobby.askForLobbies = false;
    lobby.create = true;
    lobby.join = false;
    lobby.name = buf_name;
    lobby.nb_players = 0;
    lobby.size = 4;
    lobby.lobby_uuid = boost::uuids::random_generator()();
    lobby.status = OPEN;

    boost::array<Lobby, 1> array_buf = {lobby};

    boost::system::error_code error;
    boost::asio::write(_tcp_socket, boost::asio::buffer(array_buf), error);
    if (!error) {
        std::cout << "write create Lobby" << std::endl;
    } else {
        std::cout << "write failed: " << error.message() << std::endl;
    }
}

void Client::joinLobby(boost::uuids::uuid uuid)
{
    std::string name = "joinLobby";
    std::array<char, 64> buf_name;
    for (size_t i = 0;; i++) {
        buf_name[i] = name[i];
        if (name[i] == '\0') {
            break;
        }
    }
    Lobby lobby;
    lobby.player_uuid = _uuid;
    lobby.askForLobbies = false;
    lobby.create = false;
    lobby.join = true;
    lobby.name = buf_name;
    lobby.nb_players = 0;
    lobby.size = 0;
    lobby.lobby_uuid = uuid;
    lobby.status = OPEN;

    boost::array<Lobby, 1> array_buf = {lobby};

    boost::system::error_code error;
    boost::asio::write(_tcp_socket, boost::asio::buffer(array_buf), error);
    if (!error) {
        std::cout << "write join Lobby (" << uuid << ")" << std::endl;
    } else {
        std::cout << "write failed: " << error.message() << std::endl;
    }
    boost::array<int, 1> response_buf;
    boost::asio::read(_tcp_socket, boost::asio::buffer(response_buf), error);
    if (!error) {
        if (response_buf[0] == OK) {
            std::cout << "Join accepted in lobby " << uuid << std::endl;
            // start UDP Game
        } else if (response_buf[0] == FORBIDDEN) {
            std::cout << "Something wrong when trying to join lobby " << uuid << std::endl;
        }
    } else {
        std::cout << "read failed: " << error.message() << std::endl;
    }
}

std::vector<Lobby> Client::getLobbies(void)
{
    writeLobbyData(true, false, false);
    boost::system::error_code error;
    boost::asio::read(_tcp_socket, boost::asio::buffer(_recv_buf), error);
    std::vector<Lobby> lobbies;
    if (!error) {
        if (_recv_buf[0].type == LobbyType) {
            for (std::size_t i = 0; _recv_buf[0].lobbies[i].lobby_uuid != _empty_uuid; i++) {
                lobbies.push_back(_recv_buf[0].lobbies[i]);
            }
            for (auto lobby : lobbies) {
                std::cout << "+1 lobby" << std::endl;
            }
        }
    } else {
        std::cout << "read failed: " << error.message() << std::endl;
    }
    return lobbies;
}

void Client::asyncGetLobbies(void)
{
    _tcp_socket.async_receive(boost::asio::buffer(_recv_buf, sizeof(boost::array<Data, 1>)),
        boost::bind(&Client::handleGetLobbies, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void Client::handleGetLobbies(boost::system::error_code const& error, size_t bytes_transferred)
{
    if (!error) {
        if (_recv_buf[0].type == LobbyType) {
            std::vector<Lobby> lobbies;
            for (std::size_t i = 0; _recv_buf[0].lobbies[i].lobby_uuid != _empty_uuid; i++) {
                lobbies.push_back(_recv_buf[0].lobbies[i]);
            }
            for (auto lobby : lobbies) {
                std::cout << "+1 lobby" << std::endl;
            }
        }
    } else {
        std::cout << "async receive failed: " << error.message() << std::endl;
    }
}

void Client::writeLobbyData(bool ask, bool create, bool join, std::string name,
    std::size_t nb_players, std::size_t size, boost::uuids::uuid lobby_uuid)
{
    std::array<char, 64> buf_name;
    for (size_t i = 0;; i++) {
        buf_name[i] = name[i];
        if (name[i] == '\0') {
            break;
        }
    }
    Lobby lobby = {_uuid, ask, create, join, buf_name, nb_players, size, lobby_uuid, OPEN};
    boost::array<Lobby, 1> array_buf = {lobby};
    boost::system::error_code error;
    boost::asio::write(_tcp_socket, boost::asio::buffer(array_buf), error);
    if (!error) {
        std::cout << "Client wrote data!" << std::endl;
    } else {
        std::cout << "write failed: " << error.message() << std::endl;
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
