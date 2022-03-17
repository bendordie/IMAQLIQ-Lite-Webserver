/****************************************************************************************/
/* Класс, задачей которого является отслеживание событий,                               */
/* произошедших на определенных файловых дескрипторах (в рамках сервера - на сокетах).  */
/****************************************************************************************/

#ifndef __EVENTSELECTOR_HPP__
#define __EVENTSELECTOR_HPP__

#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include "FdHandler.hpp"
#include "global_variables.hpp"

class EventSelector {


public:

    EventSelector();
    ~EventSelector();
    EventSelector(const EventSelector &other) = delete;
    EventSelector& operator=(const EventSelector &other) = delete;

    void        add(FdHandler *handler);
    bool        remove(FdHandler *handler);
    void        breakLoop();
    void        run();



private:

    FdHandler   **_fd_array;
    int         _fd_array_len;
    int         _max_fd;


};

#endif //__EVENTSELECTOR_HPP__
