#include "Client.hpp"

Client::Client(int socket_fd) : _socket_fd(socket_fd) {}

Client::~Client() {
    close(_socket_fd);
}

Client *Client::connectToServer(const std::string &address, int port) {

    int                 socket_fd;
    struct sockaddr_in  server_addr;

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket initialization error");
        return 0;
    }

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, address.c_str(), &server_addr.sin_addr) <= 0) {
        perror("Invalid address format");
        return 0;
    }
    if (connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connect error");
        return 0;
    }

    return new Client(socket_fd);
}

bool Client::sendFile(const std::string &file_path) {

    std::ifstream   ifs;

    ifs.open(file_path);
    if (!ifs.is_open()) {
        std::cerr << "Error: Can't open file" << std::endl;
        return false;
    }

    std::string buffer;
    for (int i = 0; !ifs.eof() ; ++i) {

        std::getline(ifs, buffer);
        if (!ifs.eof())
            buffer += '\n';

        std::cout << i << " BUFFER: " << buffer << std::endl;

        if (!ifs.eof() && ifs.fail()) {
            std::cerr << "Error: File reading error" << std::endl;
            ifs.close();
            return false;
        }
        send(_socket_fd, buffer.c_str(), buffer.length(), 0);
        buffer.clear();
    }

    return true;
}
