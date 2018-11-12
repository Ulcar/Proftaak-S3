#include "interface.h"
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
std::vector<Interface*> interfaces; 
std::mutex mtx;
int maxFd;


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


void connectClient(int socketFd, int max_sd)
{
    int connectFd = accept(socketFd, NULL, NULL);
    if (connectFd < 0)
    {
        perror("accept failed");
        close(socketFd);
        exit(EXIT_FAILURE);
    }
    
    Socket* socket = new Socket(connectFd);
    std::cout << "Socket " << connectFd - socketFd - 1 << " connected\n";

    if(!socket->Read())
    {
        delete socket;
        return;
    }

    std::vector<std::string> message = Protocol::FromClient(socket->getPrevMessage());
    
    if(message.size == 3)
    {
        if(message.at(0) == "0")
        {
            Machine* machine;
            switch(message.at(1).at(0))
            {
            case '0':
                machine = new Wasmachine(message.at(2));
                break;
            case '1':
                machine = new Wasmachine(message.at(2));
                break;
            case '2':
                machine = new Wasmachine(message.at(2));
                break;
            case '3':
                machine = new Wasmachine(message.at(2));
                break;
            default:
                socket->QueSend(Protocol::ToClient(CODE_CONNECT, 1));
                socket->Beat();
                delete socket;
                return;
            }
            socket->QueSend(Protocol::ToClient(CODE_CONNECT, 0));
            socket->Beat();
            machine->socket = socket;
            machines.push_back(machine);
            return;
        }
    }
    
    message = Protocol::FromInterface(socket->getPrevMessage());
    
    if(message.size == 2)
    {
        Interface* interface = new Interface(message.at(1));
        socket->QueSend(Protocol::ToClient(CODE_CONNECT, 0));
        socket->Beat();
        interface->socket = socket;
        interfaces.push_back(interface);
        return;
    }
}

void readClient(int indexSocket)
{
    Socket* tempsocket = machines.at(indexSocket)->socket;
    std::cout << "Client '" << indexSocket << "' || ";
    if(!tempsocket->Read())
    {
        machines.erase(machines.begin() + indexSocket);
        delete tempsocket;
        tempsocket = nullptr;
    }
}


static void setQuit(){
    std::unique_lock<std::mutex> lock (mtx);
    quit = true;
}

static bool askQuit(){
    std::unique_lock<std::mutex> lock (mtx);
    return quit;
}


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




int main( void )
{  
    std::cout << "------------------\n  Setting up Server\n";
    int masterFd;

    setup(&masterFd);

    std::thread Thread(HandleUserInput);
    std::cout << "  Server started\n------------------\n";

    while (!askQuit())
    {        
        fd_set readFds;
        FD_ZERO(&readFds);
        FD_SET(masterFd, &readFds);
        maxFd = masterFd;

        for(uint i = 0; i < machines.size(); i++)              
        {
                int sd = machines[i]->socket->getSocketFd();
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

        else // found activity, find outConnections
        {
            if (FD_ISSET(masterFd, &readFds))
            {
                connectClient(masterFd, maxFd);
            }
            else
            {
                for(size_t i = 0; i < machines.size(); i++)
                {
                    Socket* tempsocket = machines.at(i)->socket;
                    if (FD_ISSET(tempsocket->getSocketFd(), &readFds))
                    {
                        readClient(i);
                    }
                }
            }
        }
    }

    std::cout << "\n------------------\n  Stopping\n";
    
    Thread.detach();

    std::cout << "  Server Stopped\n------------------\n\n";

    return 0;
}