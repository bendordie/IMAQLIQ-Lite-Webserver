#include <iostream>
#include <stdlib.h>
#include "Client.hpp"


int main(int argc, char* argv[]) {

    if (argc != 4) {
        std::cerr << "Error: Wrong number of arguments (expected 3: <ip> <port> <file_path>)" << std::endl;
        exit(1);
    }

    int port = std::atoi(argv[2]);
    if (port > INT16_MAX || port < 1) {
        std::cerr << "Error: Port value is invalid (try 1...65536)" << std::endl;
        exit(1);
    }

    Client  *client = Client::connectToServer(argv[1], port);
    if (!client) {
        std::cerr << "Error: Can't connect to server: " << strerror(errno) << std::endl;
        exit(1);
    }

    bool send_failed = !client->sendFile(argv[3]);
    if (send_failed) {
        std::cerr << "Error: Can't send file to server: " << strerror(errno) << std::endl;
        exit(1);
    }
    delete client;

    return 0;
}
