#ifndef DRONE_CONTROLLER_UDP_RECEIVER_H
#define DRONE_CONTROLLER_UDP_RECEIVER_H

#pragma once

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include <vector>
#include <cstdint>

class UDP_Receiver {
public:
    UDP_Receiver(); // Constructor
    explicit UDP_Receiver(int port);

    bool start_UDP_receiver(); // Open socket and connect to server.
    bool close_UDP_receiver(); // Disconnect from server and close socket.

    std::vector<uint8_t> receive_packet(); // Receives a UDP packet.

protected:
    int sockfd;
    int port;
    bool connected;

    char buffer[65507];
    socklen_t len;

    struct sockaddr_in serveraddr{};
    struct sockaddr_in clientaddr{};



};


#endif //DRONE_CONTROLLER_CONNECTION_H
