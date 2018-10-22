#include "client.h"
#include "socket.h"
#include "protocol.h"

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <vector>
//#include <thread> 


#define SOCKET_SIZE 20

//Client == Interface (C#)
//Socket = machines (C++)

bool quit;
std::vector<Socket> sockets; 



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
    
    sockets.push_back(Socket(connectFd));
    std::cout << "Connected to: " << connectFd << "\n";
}

void readClient(int master)
{
    for(size_t i = 0; i < sockets.size(); i++)
    {
        Socket* tempsocket = &sockets.at(i);
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


static void HandleUserInput()
{   
    std::cout << "command:\n";
    std::string commando;
    std::getline(std::cin, commando);
    
    std::vector<std::string> commandos = Protocol::SplitString(commando, ' ');

    try
    {
        if ((commandos.at(0) == "exit") || (commandos.at(0) == "quit"))
        {
            quit = true;
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




int main( void )
{  
    std::cout << "------------------\n  Setting up Server\n";
    quit = false;
    //Client* client = new Client();
    //Socket* socket = new Socket();
    //std::thread inputThread (HandleUserInput); 
    int max_sd = 0;
    std::string buffer;
    fd_set master;
    int socketFd;
    
    setup(&socketFd);
    std::cout << "  Server started\n------------------\n";
    
    /*
    //For userinput-handling
    while(true){
        HandleUserInput();
    }*/

    while(!quit){

        FD_ZERO(&master);

        FD_SET(socketFd, &master);
        max_sd = socketFd;

        for (size_t i = 0 ; i < sockets.size() ; i++) 
        {
            int sd = sockets.at(i).getSocketFd();;
             
            if(sd > 0)
                FD_SET( sd , &master);
             
            if(sd > max_sd)
                max_sd = sd;
        }
        timeval timer;
        timer.tv_sec = 1;

        int socketCount = select(max_sd + 1, &master, NULL, NULL, &timer);

        if (socketCount < 0) 
        {
            printf("select error");
        }
        
        if(socketCount > 0)
        {
            if(FD_ISSET(socketFd, &master))
            {
                connectClient(socketFd, max_sd);
            }
            else
            {
                readClient(socketFd);
            }
        }
    }

    if(false)
    {
        HandleUserInput();
    }

    std::cout << "\n------------------\n  Server Stopped\n------------------\n\n";
    
    return 0;
}
