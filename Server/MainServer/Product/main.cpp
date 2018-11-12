#include "client.h"
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
std::vector<Machine*> sockets; 
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

    Machine* machine = new Wasmachine();
    machine->socket = socket;
    sockets.push_back(machine);
}

void readClient(int indexSocket)
{
    Socket* tempsocket = sockets.at(indexSocket)->socket;
    std::cout << "Client '" << indexSocket << "' || ";
    if(tempsocket->Read() == "")
    {
        sockets.erase(sockets.begin() + indexSocket);
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

        for(uint i = 0; i < sockets.size(); i++)              
        {
                int sd = sockets[i]->socket->getSocketFd();
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
                for(size_t i = 0; i < sockets.size(); i++)
                {
                    Socket* tempsocket = sockets.at(i)->socket;
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