#include "algorithm_test.h"
#include "errorlogger.h"
#include "debuglogger.h"
#include "client.h"
#include "socketHandler.h"
#include "consoleHandler.h"
#include "database.h"
#include "machine.h"
#include "protocol.h"

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <mutex>
#include <unistd.h>
#include <vector>
#include <thread> 

bool quit = false;
Database* database;
iAlgorithm* algorithm;
std::mutex mtx;
std::thread socketThread;
std::thread consoleThread;


static void Setup()
{
    database = new Database();
    algorithm = new Algorithm_test(database);
    socketThread = std::thread(SocketHandler::RunSocketHandler, database);
    consoleThread = std::thread(ConsoleHandler::RunConsoleHandler, database);

    Errorlogger::Record("System startup", "main");
    Errorlogger::LiveErrorLogging = true;

    DebugLogger::LiveDebugLogging = true;
    DebugLogger::Record("System startup", "main");
}

static void Loop()
{
    algorithm->Beat();
}

static void ShutDown()
{    
    consoleThread.detach();
    socketThread.detach();

    delete database;

    Errorlogger::Record("System shutdown", "main");
    DebugLogger::Record("System shutdown", "main");
}

//------------------------------------------------------------------------------//
//                               Main                                           //
//------------------------------------------------------------------------------//


int main( void )
{  
    Setup();

    while (!database->AskQuit())
    {
        Loop();
    }

    ShutDown();

    return 0;
}