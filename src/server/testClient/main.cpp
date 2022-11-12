/*
** EPITECH PROJECT, 2022
** main
** File description:
** testClient
*/

#include "../../client/Client.hpp"

int main(void)
{
    Client client("127.0.0.1", 10001);
    try {
        client.sendData(NONE);
        // client.asyncReceiveData();
        while (true) {
            client.sendData(UP);
            // sleep(1);
            boost::array<SpriteData, 16> recv_buf;
            client.receiveData(recv_buf);
            for (int i = 0; recv_buf[i].id != 0; i++) {
                std::cout << "id: " <<
                    recv_buf[i].id << "\t-> x: " <<
                    recv_buf[i].coords.first << "\t y: "<<
                    recv_buf[i].coords.second << std::endl;
            }
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
