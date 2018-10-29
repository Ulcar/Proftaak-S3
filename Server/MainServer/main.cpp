#include "client.h"
#include "socket.h"
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
std::vector<Socket*> sockets; 
std::mutex mtx;
int maxFd;


void setup(int *socketFd)
{
    *socketFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketFd < 0)
    {
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in sa;
    memset(&sa, 0, sizeof sa);
    sa.sin_family = AF_INET;
    sa.sin_port = Protocol::GetPort();
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
    
    sockets.push_back(new Socket(connectFd));
    std::cout << "Connected to: " << connectFd << "\n";
}

void readClient(int master)
{
    for(size_t i = 0; i < sockets.size(); i++)
    {
        Socket* tempsocket = sockets.at(i);
        if(tempsocket->getSocketFd() == master)
        {   
            std::cout << "Client '" << i << "' || ";
            if(tempsocket->Read() == "")
            {
                sockets.erase(sockets.begin() + i);
                delete tempsocket;
                continue;
            }
        }
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
    
    std::thread Thread(HandleUserInput);
     int listenFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    maxFd = listenFd;
    if (listenFd < 0)
    {
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in sa;
    memset(&sa, 0, sizeof sa);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(2018);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listenFd, (struct sockaddr*)&sa, sizeof sa) < 0)
    {
        perror("bind failed");
        close(listenFd);
        exit(EXIT_FAILURE);
    }

    if (listen(listenFd, 20) < 0)
    {
        perror("listen failed");
        close(listenFd);
        exit(EXIT_FAILURE);
    }

    while (!askQuit())
    {        
        fd_set readFds;
        FD_ZERO(&readFds);
        FD_SET(listenFd, &readFds);
        maxFd = listenFd;

          for(uint i = 0; i < sockets.size(); i++)              
            {
                int sd = sockets[i]->getSocketFd();
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
        timeout.tv_sec = 2;
        timeout.tv_usec = 0;

        int nrSockets = select(maxFd + 1, &readFds, NULL, NULL, &timeout);

        if (nrSockets < 0) // error situation
        {
            perror("error from calling socket");
        }
        else if (nrSockets == 0) // timeout
        {
            std::cout << "still listening\n";
        }

         else // found activity, find outConnections
        {
            if (FD_ISSET(listenFd, &readFds))
            {
                int communicationFd = accept(listenFd, NULL, NULL);;
                if (communicationFd < 0)
                {
                    perror("accept failed");
                    close(listenFd);
                    exit(EXIT_FAILURE);
                }
                if(communicationFd > maxFd)
                {
                    maxFd = communicationFd;
                }
                Socket* data = new Socket(communicationFd);
                sockets.push_back(data);
                std::cout << "client connected";
            }
            else
            {

            }
        }
    }

    Thread.detach();
}