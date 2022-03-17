#include "WebServer.hpp"

WebServer::WebServer(EventSelector *event_selector, int fd)
    : FdHandler(fd, true), _event_selector(event_selector) {

    _event_selector->add(this);
}

WebServer::~WebServer() {

    for (std::list<WebSession*>::iterator it = _session_list.begin(); it != _session_list.end(); ++it) {
        _event_selector->remove((*it));
    }
    _event_selector->remove(this);
}

WebServer *WebServer::init(EventSelector *event_selector, int port) {

    int                 listen_socket, option, result;
    struct sockaddr_in  addr;

    listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_socket == -1)
        return 0;

    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    result = bind(listen_socket, (struct sockaddr*)&addr, sizeof(addr));
    if (result == -1)
        return 0;

    result = listen(listen_socket, GlobalVars::g_BACKLOG);
    if (result == -1)
        return 0;

    return new WebServer(event_selector, listen_socket);
}

void WebServer::handle(bool read, bool write) {

    if (!read)
        return;
    int                 client_socket;
    struct sockaddr_in  addr;
    socklen_t           len = sizeof(addr);

    client_socket = accept(this->getFd(), (struct sockaddr*)&addr, &len);
    if (client_socket == -1)
        return;

    fcntl(client_socket, F_SETFL, O_NONBLOCK);

    WebSession  *session = new WebSession(this, client_socket);
    _session_list.push_front(session);
    _event_selector->add(session);
}

void WebServer::removeSession(WebSession *session) {

    _event_selector->remove(session);
    for (std::list<WebSession*>::iterator it = _session_list.begin(); it != _session_list.end(); ++it) {
        if ((*it) == session) {
            _session_list.erase(it);
            delete *it;
            return;
        }
    }
}