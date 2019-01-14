#include "client.h"
#include "consoleHandler.h"
#include "database.h"
#include "logger.h"
#include "machine.h"
#include "protocolHandler.h"
#include "socketHandler.h"
#include "translator.h"

#include <thread>
#include <vector>
 

bool quit = false;
Database* database;
std::mutex mtx;
std::thread socketThread;
std::thread consoleThread;
std::thread protocolThread;


void Setup()
{
    Logger::Record(true, "System startup", "main");
    Logger::LiveErrorLogging = true;
    Logger::LiveHeartBeat = false;
    Logger::LiveDebugLogging = true;
    Logger::Record(false, "System startup", "main");

    database = new Database();
    socketThread = std::thread(SocketHandler::RunSocketHandler, database);
    consoleThread = std::thread(ConsoleHandler::RunConsoleHandler, database);
    protocolThread = std::thread(ProtocolHandler::RunProtocolHandler, database);
}

void Loop()
{

}

void Shutdown()
{    
    consoleThread.detach();         //Stop reading console
    socketThread.join();            //Wait untill all sockets are handled
    protocolThread.join();          //Wait untill everything is handled

    delete database;                //Remove database safely

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

    Shutdown();

    return 0;
}