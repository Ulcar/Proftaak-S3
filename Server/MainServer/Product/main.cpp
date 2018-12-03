#include "errorlogger.h"
#include "controlpanel.h"
#include "socketHandler.h"
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




//------------------------------------------------------------------------------//
//                               Mutexes                                        //
//------------------------------------------------------------------------------//


static bool askQuit(){
    std::unique_lock<std::mutex> lock (mtx);
    return quit;
}

static void setQuit(){
    std::unique_lock<std::mutex> lock (mtx);
    quit = true;
}

//------------------------------------------------------------------------------//
//                               Console                                        //
//------------------------------------------------------------------------------//


static void HandleUserInput()
{   
    while(true)
    {
        std::cout << "command:\n";
        std::string commando;
        std::getline(std::cin, commando);
        
        std::vector<std::string> commandos = Protocol::SplitString(commando, ' ');

        try
        {
            if ((commandos.at(0) == "exit") || (commandos.at(0) == "quit"))
            {
                setQuit();
                return;
            }
            else if(commandos.at(0) == "errorlogger")
            {
                if(commandos.size() == 1)
                {
                    std::cout << "live\n";
                    std::cout << "save\n";
                }
                else
                {
                    if(commandos.at(1) == "save")
                    {
                        Errorlogger::SaveAsFile();
                    }
                    else if(commandos.at(1) == "live")
                    {
                        Errorlogger::LiveErrorLogging = !Errorlogger::LiveErrorLogging;
                        std::cout << "Live Errorlogging: " << Errorlogger::LiveErrorLogging << "\n";
                    }
                }
            }
            else
            {
                std::cout << "Invalid arg: " << commando << "\n";
            }
        }
        catch(std::exception)
        {
            std::cout << "Exception: " << commando << "/n";
        }
    }
}

//------------------------------------------------------------------------------//
//                               Main                                           //
//------------------------------------------------------------------------------//


int main( void )
{  
    std::cout << "------------------\n  Setting up Server\n";
    
    Errorlogger::LiveErrorLogging = false;
    Errorlogger::Record("System startup", "main");
    Errorlogger::LiveErrorLogging = true;

    std::thread socketThread(SocketHandler::RunSocketHandler, database);
    std::thread consoleThread(HandleUserInput);

    std::cout << "  Server started\n------------------\n";

    while (!askQuit())
    {
        std::vector<Machine*> tempMachines = database->GetMachines();
        for(Machine* machine : tempMachines)
        {
            machine->Beat();
        }
    }

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

    return 0;
}