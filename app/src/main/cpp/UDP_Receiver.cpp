//
// Created by Kris on 21/09/2025.
//

#include "UDP_Receiver.h"

// Constructors
UDP_Reciever::UDP_Reciever() {}

UDP_Reciever::UDP_Reciever(int _port) {
    port = _port;
}

// open socket and connect to server
bool UDP_Reciever::start_UDP_reciever() {
    if (connected) return true;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        connected = false;
        return false;
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0) {
        close(sockfd);
        connected = false;
        return false;
    }

    len = sizeof(clientaddr);

    connected = true;

    return true;
}

bool UDP_Reciever::close_UDP_reciever() {
    if (!connected) return true;

    close(sockfd);
    sockfd = -1;

    connected = false;

    return true;
}