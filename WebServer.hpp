#ifndef __WEBSERVER_HPP__
#define __WEBSERVER_HPP__

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <list>
#include "FdHandler.hpp"
#include "EventSelector.hpp"
#include "WebSession.hpp"
#include "global_variables.hpp"

class WebSession;

class WebServer : public FdHandler {

public:

    ~WebServer();
    WebServer(const WebServer& other) = delete;
    WebServer& operator=(const WebServer& other) = delete;

    static WebServer*           init(EventSelector *event_selector, int port);
    void                        removeSession(WebSession *session);


private:

    WebServer(EventSelector *event_selector, int fd);

    virtual void    handle(bool read, bool write);

    EventSelector           *_event_selector;
    std::list<WebSession*>  _session_list;

};

#endif //WEBSERV_WEBSERVER_HPP
