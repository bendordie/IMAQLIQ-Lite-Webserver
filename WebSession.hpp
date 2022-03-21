/*********************************************/
/* Класс для обработки соединения с клиентом */
/*********************************************/

#ifndef __WEBSESSION_HPP__
#define __WEBSESSION_HPP__

#include <unistd.h>
#include <iostream>
#include <cstring>
#include <list>
#include <stdio.h>
#include <fstream>
#include <syslog.h>
#include "WebServer.hpp"
#include "FdHandler.hpp"
#include "global_variables.hpp"

class WebServer;

class WebSession : public FdHandler {

    friend class WebServer;

    WebSession(WebServer *master, int fd);
    ~WebSession();
    WebSession(const WebSession& other);
    WebSession& operator=(const WebSession& other);

public:

    static int          id_generator;

private:

    int                 _id;
    char                _buffer[4096+1];
    WebServer           *_master;

    void                handle(bool read, bool write);
    void                handleRequest();
    bool                receiveText();
    bool                saveTextToFile();
    void                writeErrorToLog(const std::string &error);


};

#endif //__WEBSESSION_HPP__
