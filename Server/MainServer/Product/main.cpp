#include "client.h"
#include "consoleHandler.h"
#include "database.h"
#include "logger.h"
#include "machine.h"
#include "protocolHandler.h"
#include "socketHandler.h"
#include "translator.h"
#include "wasbak.h"

#include <thread>
#include <vector>
 

bool quit = false;
Database* database;
ProtocolHandler* protocolHandler;
std::mutex mtx;
std::thread socketThread;
std::thread consoleThread;

std::vector<Wasbak> WasToDo;
std::vector<Wasbak> finishedWas;


void Setup()
{
    Logger::Record(true, "System startup", "main");
    Logger::LiveErrorLogging = true;

    Logger::LiveDebugLogging = true;
    Logger::Record(false, "System startup", "main");

    database = new Database();
    protocolHandler = new ProtocolHandler(database);
    socketThread = std::thread(SocketHandler::RunSocketHandler, database);
    consoleThread = std::thread(ConsoleHandler::RunConsoleHandler, database);
}

void Loop()
{
    protocolHandler->HandleMessages();
}

void ShutDown()
{    
    consoleThread.detach();
    socketThread.detach();

    delete database;
    delete protocolHandler;
    //delete iAlgorithm;

    Logger::Record(true, "System shutdown", "main");
    Logger::Record(false, "System shutdown", "main");
    
    Logger::SaveErrorAsFile();
    Logger::SaveDebugAsFile();
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