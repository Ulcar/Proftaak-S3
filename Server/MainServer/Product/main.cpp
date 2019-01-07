#include "algorithm.h"
#include "iAlgorithm.h"
#include "algorithm_easy.h"
#include "errorlogger.h"
#include "debuglogger.h"
#include "client.h"
#include "socketHandler.h"
#include "consoleHandler.h"
#include "database.h"
#include "machine.h"
#include "protocol.h"

#include <vector>
#include <thread> 

bool quit = false;
Database* database;
Algorithm* algorithm;
iAlgorithm* iAlgorithm;
std::mutex mtx;
std::thread socketThread;
std::thread consoleThread;


void Setup()
{
    Errorlogger::Record("System startup", "main");
    Errorlogger::LiveErrorLogging = true;

    DebugLogger::LiveDebugLogging = true;
    DebugLogger::Record("System startup", "main");

    database = new Database();
    iAlgorithm = new Algorithm_easy(database);
    algorithm = new Algorithm(database, iAlgorithm);
    socketThread = std::thread(SocketHandler::RunSocketHandler, database);
    consoleThread = std::thread(ConsoleHandler::RunConsoleHandler, database);
}

void Loop()
{
    algorithm->HandleMessages();
}

void ShutDown()
{    
    consoleThread.detach();
    socketThread.detach();

    delete database;
    delete algorithm;

    Errorlogger::Record("System shutdown", "main");
    DebugLogger::Record("System shutdown", "main");
    
    Errorlogger::SaveAsFile();
    DebugLogger::SaveAsFile();
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