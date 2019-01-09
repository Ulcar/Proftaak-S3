#include "protocol.h"

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>


static void sendMessageToClient(int *connectFd, std::string text)
{
    size_t nrBytesRec = send(*connectFd, text.c_str(), text.length(), 0);
    if (nrBytesRec != text.length())
    {
        std::cout << "not everything is sent (" << nrBytesRec << "/" << text.length() << " bytes sent)\n";
    }
}

static std::string readMessageFromClient(int *connectFd)
{
    const int BufferSize = 100;
    char buffer[BufferSize];
    int nrBytesSend = read(*connectFd, buffer, BufferSize - 1);
    if (nrBytesSend > 0)
    {
        buffer[nrBytesSend] = '\0';
        //std::cout << "received " << nrBytesSend << " bytes: " << buffer << std::endl;
    }
    else if(nrBytesSend == 0)
    {
        std::cout << "Server is shutdown. Disconnected\n";
        close(*connectFd);
        return "";
    }
    return buffer;
}  
  
  
  
  
void setupServer  (int *socketFd)
{  
    struct socka  ddr_in sa;
    memset(&sa,   0, sizeof sa);
    sa.sin_famil  y = AF_INET;
    sa.sin_port   = PortNumber;
    sa.sin_addr.  s_addr = htonl(INADDR_ANY);

    //create socket
    *socketFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketFd < 0)
    {
        perror("cannot create socket\n");
        exit(EXIT_FAILURE);
    }

    //bind socket to port
    if (bind(*socketFd, (struct sockaddr*)&sa, sizeof sa) < 0)
    {
        perror("bind failed");
        close(*socketFd);
        exit(EXIT_FAILURE);
    }
    
    //listen for connection
    if (listen(*socketFd, 1) < 0)
    {
        perror("listen failed\n");
        close(*socketFd);
        exit(EXIT_FAILURE);
    }
     std::cout << "------------------------\n     Server started  \n------------------------ \n";
}

int connectClient(int socketFd)
{
    int connectFd = accept(socketFd, NULL, NULL);
    if (connectFd < 0)
    {
        perror("accept failed");
        close(socketFd);
        exit(EXIT_FAILURE);
    }

    return connectFd;
}


int main(void)
{

    int socketCount;
    int socketFd;  
    int connectFd;
    setupServer(&socketFd);

    while(true)
    {
        std::cout << "halloWorld\n";
        if (socketCount < 0)
        {
            printf("Error");
        }

        else if (socketCount == 0)
        {
            std::cout << "awaiting connection\n";
            connectFd = connectClient(socketFd);
            socketCount++;
        }

        else if (socketCount > 0)
        {
            std::cout << "reading message\n";

            //readMessageFromClient(&connectFd);

            if (readMessageFromClient(&connectFd).compare(0,2,"&0"))
            {
                std::cout << readMessageFromClient(&connectFd);
            }
            else
            {
                std::cout << readMessageFromClient(&connectFd) << "\n";
                std::string message;
                std::cin >> message;
                sendMessageToClient(&socketFd, message);
            }
        }

        std::cout << "loop\n";
    }
    return EXIT_SUCCESS;
}