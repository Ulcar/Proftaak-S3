#ifndef CONSOLEHANDLER_H
#define CONSOLEHANDLER_H

#include "database.h"
#include "errorlogger.h"

class ConsoleHandler
{
    public:
        static void RunConsoleHandler(Database* tempdatabase);
        static std::string HandleConsoleCommando(std::string commando);

    private:
        static Database* database;
};

#endif