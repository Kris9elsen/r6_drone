#include "UDP_Receiver.h"

// Constructors
UDP_Receiver::UDP_Receiver() : sockfd(-1), port(0), connected(false), len(0) {}

UDP_Receiver::UDP_Receiver(int port): sockfd(-1), port(port), connected(false), len(0) {}

// Open socket and connect to server
bool UDP_Receiver::start_UDP_receiver() {
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

// Close socket and stop connection
bool UDP_Receiver::close_UDP_receiver() {
    if (!connected) return true;

    close(sockfd);
    sockfd = -1;

    connected = false;

    return true;
}

// Receive UDP packet
std::vector<uint8_t> UDP_Receiver::receive_packet() {
    ssize_t n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientaddr, &len);

    if (n>0) {
        std::vector<uint8_t> packet(buffer, buffer + n);
        return packet;
    }

    return {};
}