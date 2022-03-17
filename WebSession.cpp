#include "WebSession.hpp"

int WebSession::id_generator = 0;

WebSession::WebSession(WebServer *master, int fd)
: FdHandler(fd, true), _id(id_generator++), _master(master) {
    bzero(_buffer, sizeof(_buffer));
}

WebSession::~WebSession() {}

void WebSession::writeErrorToLog(const std::string &error) {
    openlog(GlobalVars::g_PROGRAM_NAME, LOG_PID | LOG_CONS, LOG_DAEMON);
    syslog(LOG_ERR, "%s", error.c_str());
    closelog();
}

bool WebSession::receiveText() {

    size_t bytes_read;

    bytes_read = recv(getFd(), _buffer, sizeof(_buffer) - 1, 0);
    _buffer[bytes_read] = '\0';
    if (bytes_read < 0) {
        writeErrorToLog("Read socket: Error has been occurred");
        return false;
    }
    if (bytes_read == 0) {
        return false;
    }

    return true;
}

bool WebSession::saveTextToFile() {

    std::string     file_path = "./file_from_session_" + std::to_string(_id);
    std::ofstream   ofs;

    ofs.open(file_path, std::ios::in | std::ios::out | std::fstream::app);
    if (!ofs.is_open()) {
        writeErrorToLog("WebSession " + std::to_string(getFd()) + ": Error: Can't create/open file");
        return false;
    }
    ofs.write(_buffer, strlen(_buffer));
    if (ofs.fail()) {
        writeErrorToLog("WebSession " + std::to_string(getFd()) + ": Error: Can't save data");
        return false;
    }

    return true;
}

void WebSession::handleRequest() {

    bool receive_failed = !receiveText();
    if (receive_failed) {
        _master->removeSession(this);
        return;
    }
    bool save_failed = !saveTextToFile();
    if (save_failed) {
        _master->removeSession(this);
        return;
    }
}

void WebSession::handle(bool read, bool write) {

    if (read) {
        handleRequest();
    }
}
