#include <iostream>
#include <vector>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <vector>
//#include <thread> 

#include "client.h"
#include "socket.h"

#define SOCKET_SIZE 20

//Client == Interface (C#)
//Socket = machines (C++)

bool quit;
int PortNumber = 2018;
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
    sa.sin_port = PortNumber;
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
     std::cout << "------------------------\n     Server started<standard message>  \n------------------------ \n";
}
//----------------------------------------------------------------


static void sendMessage(int *socketFd, std::string text)
{
    size_t nrBytesRec = send(*socketFd, text.c_str(), text.length(), 0);
    if (nrBytesRec != text.length())
    {
        std::cout << "not everything is sent (" << nrBytesRec << "/" << text.length() << " bytes sent)\n";
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

void readClient(fd_set &master)
{
    for(int i = 0; i < sockets.size; i++)
    {
        Socket* tempsocket = &sockets.at(i);
        if(*tempsocket->getSocketFd == &master)
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
//-------------------------------------------------------------------------
        
static void HandleUserInput()
{
    while(!quit)
    {
        std::string commando;
        std::cin >> commando;
        std::cin.ignore();
        
        //string[] commando = Console.ReadLine().ToLower().Split(' ');

        try
        {
            if ((commando == "exit") || (commando == "quit"))
            {
                quit = true;
            }
            else
            {
                std::cout << "Invalid arg: " << commando;
            }
        }
        catch(std::exception)
        {
            std::cout << "Exception: " << commando;
        }
    }
}

int main( void )
{  
    std::cout << "------------------\n  Setting up Server\n------------------\n";
    quit = false;
    //Client* client = new Client();
    //Socket* socket = new Socket();
    //std::thread inputThread (HandleUserInput); 
    int max_sd = 0;
    int client_socket[SOCKET_SIZE];
    fd_set master;
    int socketFd;
    
    setup(&socketFd);
    std::cout << "------------------\n  Server started\n------------------\n";

    while(!quit){

        FD_ZERO(&master);

        FD_SET(socketFd, &master);
        max_sd = socketFd;

        for (size_t i = 0 ; i < sockets.size ; i++) 
        {
            int sd = sockets.at(i).getSocketFd();;
             
            if(sd > 0)
                FD_SET( sd , &master);
             
            if(sd > max_sd)
                max_sd = sd;
        }

        int socketCount = select(max_sd + 1, &master, NULL, NULL, NULL);

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
                readClient(master);
            }
        }
    }

    HandleUserInput();

    std::cout << "\nServer Stopped...\n\n";
    
    return 0;
}
