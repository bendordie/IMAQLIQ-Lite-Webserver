#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "WebServer.hpp"
#include "global_variables.hpp"

void signalHandler(int) {
    GlobalVars::g_SHUT_DOWN = true;
}

int main(void) {

    pid_t   pid = fork();
    if(pid < 0) {
        perror("Error: ");
        exit(1);
    }
    else if (pid != 0)
        exit(0);

    setsid();
    EventSelector   *event_selector = new EventSelector;
    WebServer       *server =   WebServer::init(event_selector, GlobalVars::g_PORT);
    if (!server) {
        perror("Error: ");
        exit(1);
    }
    signal(SIGTERM, signalHandler);
    signal(SIGHUP, signalHandler);

    event_selector->run(); // while(!SIGTERM && !SIGHUP) loop

    delete server;
    delete event_selector;

    return 0;
}

