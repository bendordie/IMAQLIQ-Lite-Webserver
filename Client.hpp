#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fstream>
#include <strings.h>

class Client {

public:

    Client(int socket_fd);
    ~Client();

    static Client*  connectToServer(const std::string &address, int port);
    bool            sendFile(const std::string &file_path);


private:

    int _socket_fd;

};

#endif //__CLIENT_HPP__
