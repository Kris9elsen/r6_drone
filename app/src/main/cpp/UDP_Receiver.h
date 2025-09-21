//
// Created by Kris on 21/09/2025.
//

#ifndef DRONE_CONTROLLER_UDP_RECEIVER_H
#define DRONE_CONTROLLER_UDP_RECEIVER_H

#pragma once

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>

class UDP_Reciever {
public:
    UDP_Reciever(); // Constructor
    explicit UDP_Reciever(int _port);

    bool start_UDP_reciever(); // Open socket and connect to server
    bool close_UDP_reciever(); // Disconnect from server and close socket


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
