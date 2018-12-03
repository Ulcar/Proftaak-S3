#include "errorlogger.h"
#include "controlpanel.h"
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


#define SOCKET_SIZE 20

//Client == Interface (C#)
//Socket = machines (C++)

bool quit = false;
std::vector<Machine*> machines; 
std::vector<ControlPanel*> controlPanels; 
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


static std::vector<Machine*> askMachines(){
    std::unique_lock<std::mutex> lock (mtx);
    return machines;
}

static void setMachines(Machine* machine){
    std::unique_lock<std::mutex> lock (mtx);
    machines.push_back(machine);
}


static std::vector<ControlPanel*> askControlPanels(){
    std::unique_lock<std::mutex> lock (mtx);
    return controlPanels;
}

static void setControlPanel(ControlPanel* controlpanel){
    std::unique_lock<std::mutex> lock (mtx);
    controlPanels.push_back(controlpanel);
}

//------------------------------------------------------------------------------//
//                               Console                                        //
//------------------------------------------------------------------------------//


static void HandleUserInput()
{   
    Errorlogger::LiveErrorLogging = true;
    Errorlogger::Record("System startup", "main");

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
//                               Socket                                         //
//------------------------------------------------------------------------------//

void setup(int *socketFd)
{
    *socketFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (*socketFd < 0)
    {
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in sa;
    memset(&sa, 0, sizeof sa);
    sa.sin_family = AF_INET;
    sa.sin_port = Protocol::GetPort();
    //sa.sin_port = htons(Protocol::GetPort());
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(*socketFd, (struct sockaddr*)&sa, sizeof sa) < 0)
    {
        perror("bind failed");
        close(*socketFd);
        exit(EXIT_FAILURE);
    }
    
    if (listen(*socketFd, SOCKET_SIZE) < 0)
    {
        perror("listen failed");
        close(*socketFd);
        exit(EXIT_FAILURE);
    }
}

Machine* CreateNewMachine(char type, std::string macAdress)
{
    std::vector<Machine*> tempMachines = askMachines();
    for(Machine* machine : tempMachines)
    {
        if(machine->GetMacAdress() == macAdress)
        {
            return machine;
        }
    }

    Machine* machine;

    switch(type)
    {
    case '0':
        machine = new Wasmachine(macAdress);
        break;
    case '1':
        machine = new Wasmachine(macAdress);
        break;
    case '2':
        machine = new Wasmachine(macAdress);
        break;
    case '3':
        machine = new Wasmachine(macAdress);
        break;
    default:
        machine = nullptr;
    }
    return machine;
}


void connectClient(int socketFd)
{
    int connectFd = accept(socketFd, NULL, NULL);
    if (connectFd < 0)
    {
        perror("accept failed");
        close(socketFd);
        exit(EXIT_FAILURE);
    }
    
    Socket* socket = new Socket(connectFd);
    std::cout << "Socket " << connectFd << " connected\n";

    if(!socket->Read())
    {
        delete socket;
        return;
    }

    std::vector<std::string> message = Protocol::FromClient(socket->ReadLastMessage());
    
    if(message.size() == 3)
    {
        if(message.at(0) == "0")
        {
            Machine* machine = CreateNewMachine(message.at(1).at(0), message.at(2));
            if(machine == nullptr)
            {
                delete socket;
                return;
            }

            socket->NewSendMessage(Protocol::ToClient(CODE_CONNECT, 0));
            socket->TrySend();
            machine->SetSocket(socket);
            setMachines(machine);
            return;
        }
    }
    
    message = Protocol::FromInterface(socket->ReadLastMessage());
    
    if(message.size() == 2)
    {
        if(message.at(0) == "0")
        {
            ControlPanel* controlpanel = new ControlPanel(message.at(1));
            socket->NewSendMessage(Protocol::ToClient(CODE_CONNECT, 0));
            socket->TrySend();
            controlpanel->SetSocket(socket);
            setControlPanel(controlpanel);
            return;
        }
    }
}

bool readClient(Socket* socket)
{
    std::cout << "Client '" << socket->getSocketFd() << "' || ";
    if(!socket->Read())
    {
       return false;
    }
    return true;
}

static void socketHandler()
{
    int masterFd;
    int maxFd;

    setup(&masterFd);

    std::cout << "  Socket started\n";

    while (true)
    {        
//is dit echt nodig?     
        fd_set readFds;
        FD_ZERO(&readFds);
        FD_SET(masterFd, &readFds);
        maxFd = masterFd;

        std::vector<Machine*> tempMachines = askMachines();
        for(Machine* machine : tempMachines)              
        {
                int sd = machine->GetSocket()->getSocketFd();
                 //if valid socket descriptor then add to read list
            if(sd > 0)
            {
                FD_SET(sd,&readFds);
            }
                
            //highest file descriptor number, need it for the select function
            if(sd > maxFd)
            {
                maxFd = sd;
            }
        }

        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        int nrSockets = select(maxFd + 1, &readFds, NULL, NULL, &timeout);


        if (nrSockets < 0) // error situation
        {
            perror("error from calling socket");
        }
        else if (nrSockets == 0) // timeout
        {
            //nothing
        }
//to hier
                
        if (FD_ISSET(masterFd, &readFds))
        {
            connectClient(masterFd);
        }

        tempMachines = askMachines();
        for(Machine* tempmachine : tempMachines)
        {
            Socket* tempsocket = tempmachine->GetSocket();

            if(tempsocket == nullptr)
            {
                continue;
            }

            //Try Sending a message
            tempsocket->TrySend();

            //Try Reading a message
            if (FD_ISSET(tempsocket->getSocketFd(), &readFds))
            {
                if(!readClient(tempsocket))
                { 
                    tempmachine->SetSocket(nullptr);
                    tempsocket = nullptr;
                }
            }
        }

        std::vector<ControlPanel*> tempControlPanels = askControlPanels();
        for(ControlPanel* tempcontrolpanel : tempControlPanels)
        {
            Socket* tempsocket = tempcontrolpanel->GetSocket();

            tempsocket->TrySend();

            if (FD_ISSET(tempsocket->getSocketFd(), &readFds))
            {
                if(!readClient(tempsocket))
                { 
                    tempcontrolpanel->SetSocket(nullptr);
                    tempsocket = nullptr;
                }
            }
        }
    }
}

//------------------------------------------------------------------------------//
//                               Main                                           //
//------------------------------------------------------------------------------//


int main( void )
{  
    std::cout << "------------------\n  Setting up Server\n";

    std::thread socketThread(&socketHandler);
    std::thread consoleThread(HandleUserInput);

    std::cout << "  Server started\n------------------\n";

    while (!askQuit())
    {
        std::vector<Machine*> tempMachines = askMachines();
        for(Machine* machine : tempMachines)
        {
            machine->Beat();
        }
    }

    std::cout << "\n------------------\n  Stopping\n";
    
    consoleThread.detach();
    socketThread.detach();

    std::vector<Machine*> tempMachines = askMachines();
    for(Machine* machine : tempMachines)
    {
        machine->SetSocket(nullptr);
    }

    std::vector<ControlPanel*> tempControlPanels = askControlPanels();
    for(ControlPanel* controlpanel : tempControlPanels)
    {
        controlpanel->SetSocket(nullptr);
    }

    std::cout << "  Server Stopped\n------------------\n\n";

    return 0;
}