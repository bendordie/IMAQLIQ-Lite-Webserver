#include <unistd.h>
#include <signal.h>
#include "WebServer.hpp"
#include "global_variables.hpp"

void signalHandler(int status) {

    if (WIFSIGNALED(status))
    {
        if (status == SIGTERM || status == SIGHUP) {
            GlobalVars::g_SHUT_DOWN = true;
        }
    }
    else
        exit(WEXITSTATUS(status));
}

int main(void) {

    EventSelector   *event_selector = new EventSelector;
    WebServer       *server =   WebServer::init(event_selector, GlobalVars::g_PORT);

    if (!server) {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        exit(1);
    }
    pid_t pid = fork();
    if(pid < 0) {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        exit(1);
    }
    else if (pid != 0)
        exit(0);
    setsid();
    signal(SIGTERM, signalHandler);
    signal(SIGHUP, signalHandler);

    event_selector->run();

    delete server;
    delete event_selector;

    return 0;
}

