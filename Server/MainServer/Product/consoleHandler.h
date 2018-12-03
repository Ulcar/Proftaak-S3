#ifndef CONSOLEHANDLER_H
#define CONSOLEHANDLER_H

#include "database.h"
#include "errorlogger.h"

class ConsoleHandler
{
    public:
        static void RunConsoleHandler(Database* tempdatabase);

    private:
        static Database* database;
};

#endif