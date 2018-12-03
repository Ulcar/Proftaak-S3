#include "errorlogger.h"
#include "controlpanel.h"
#include "socketHandler.h"
#include "consoleHandler.h"
#include "database.h"
#include "wasmachine.h"
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



//Client == Interface (C#)
//Socket = machines (C++)

bool quit = false;
Database* database = new Database;
std::mutex mtx;
std::thread socketThread;
std::thread consoleThread;


static void Setup()
{
    std::cout << "------------------\n  Setting up Server\n";

    Errorlogger::LiveErrorLogging = false;
    Errorlogger::Record("System startup", "main");
    Errorlogger::LiveErrorLogging = true;

    socketThread = std::thread(SocketHandler::RunSocketHandler, database);
    consoleThread = std::thread(ConsoleHandler::RunConsoleHandler, database);
    std::cout << "  Server started\n------------------\n";
}

static void Loop()
{
    std::vector<Machine*> tempMachines = database->GetMachines();
    for(Machine* machine : tempMachines)
    {
        machine->Beat();
    }
}

static void ShutDown()
{

    std::cout << "\n------------------\n  Stopping\n";
    
    consoleThread.detach();
    socketThread.detach();

    std::vector<Machine*> tempMachines = database->GetMachines();
    for(Machine* machine : tempMachines)
    {
        machine->SetSocket(nullptr);
    }

    std::vector<ControlPanel*> tempControlPanels = database->GetControlPanels();
    for(ControlPanel* controlpanel : tempControlPanels)
    {
        controlpanel->SetSocket(nullptr);
    }

    //delete database;

    std::cout << "  Server Stopped\n------------------\n\n";
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