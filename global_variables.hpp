#ifndef __GLOBAL_VARIABLES_HPP__
#define __GLOBAL_VARIABLES_HPP__

namespace GlobalVars {

    extern bool         g_SHUT_DOWN; // пока значение false сервер (а именно EventSelector) продолжает работу, иначе - экстренное завершение
    extern const char   g_PROGRAM_NAME[];
    extern const int    g_BACKLOG;
    extern const int    g_PORT;
}


#endif //__GLOBAL_VARIABLES_HPP__
