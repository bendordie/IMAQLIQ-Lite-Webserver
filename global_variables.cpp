#include "global_variables.hpp"

namespace GlobalVars {

    bool        g_SHUT_DOWN = false;
    bool        g_HANG_UP = false;
    const char  g_PROGRAM_NAME[] = "server";
    const int   g_BACKLOG(16);
    const int   g_PORT = 80;
}

