#include "protocol.h"

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>
#include <thread> 

std::thread socketThread;
int socketFd = 0;
bool connected = false;
std::string macAdress;

static void showMenu()
{
    std::cout << ("\n\nSocket menu\n");
    std::cout << ("===============\n");
    std::cout << ("(1) Connect to server\n");
    std::cout << ("(2) Disconnect from server\n");
    std::cout << ("(3) Request to take water\n");
    std::cout << ("(4) Stop taking water\n");
    std::cout << ("(5) Request to heat\n");
    std::cout << ("(6) Stop heating\n");
    std::cout << ("(7) Program done\n");
    std::cout << ("-----------------------\n");
    std::cout << ("(q) QUIT\n\n");
    std::cout << ("Choice : ");
}

static void sendMessage(int *socketFd, std::string text)
{
    size_t nrBytesRec = send(*socketFd, text.c_str(), text.length(), 0);
    if (nrBytesRec != text.length())
    {
        std::cout << "not everything is sent (" << nrBytesRec << "/" << text.length() << " bytes sent)\n";
    }
    std::cout << "send: " + text;
}

static std::string readMessage(int *socketFd)
{
    const int BufferSize = 100;
    char buffer[BufferSize];
    int nrBytesSend = read(*socketFd, buffer, BufferSize - 1);
    if (nrBytesSend > 0)
    {
        buffer[nrBytesSend] = '\0';
        std::cout << "received " << nrBytesSend << " bytes: " << buffer << std::endl;
    }
    else if(nrBytesSend == 0)
    {
        std::cout << "\nServer is shutdown. Disconnected\n";
        close(*socketFd);
        connected = false;
        return "";
    }
    return buffer;
}

static void connectToServer(int *socketFd, bool *connected)
{
    if(*connected){
        std::cout << ("\nAlready connected!\n");
        return;
    }
    std::cout << "Your mac Address: ";
    std::cin >> macAdress;

    *socketFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (*socketFd == -1)
    {
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in sa;
    memset(&sa, 0, sizeof sa);
    sa.sin_family = AF_INET;
    sa.sin_port = PortNumber;
    
    int result = inet_pton(AF_INET, "192.168.137.208", &sa.sin_addr);
    if (result != 1)
    {
        perror("could not convert ip address to network address structure");
        exit(EXIT_FAILURE);
    }

    result = connect(*socketFd, (struct sockaddr*)&sa, sizeof sa);

    if (result < 0)
    {
        perror("connect failed");
        close(*socketFd);
        *connected = false;
        return;
    }
    *connected = true;

    //message = Connect request + machine type + mac address whitout ":"
    sendMessage(socketFd, "&0;0;" + macAdress + "#");

    return;
}

static void disconnectFromServer(int *socketFd, bool *connected)
{
    if(!*connected){
        std::cout << ("\nNot connected yet!\n");
        return;
    }

    close(*socketFd);
    *connected = false;
    return;
}

static void sendMessageToServer(int *socketFd, bool *connected, std::string message)
{
    if(!*connected)
    {
        std::cout << ("\nNot connected yet!\n");
        return;
    }

    sendMessage(socketFd, message);
    return;
}

static void SocketReader()
{
    while(true)
    {
        if(connected)
        {
            std::string reply = readMessage(&socketFd);
            std::cout << reply;
        }
    }
}

int main(void)
{
    socketThread = std::thread(SocketReader);

    bool quit = false;

    

    while (!quit)
    {
        char choice = '\0';
        std::string input;
        std::string message;
        std::string reply;

        showMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice)
        {
            case '1' :
                connectToServer(&socketFd, &connected);
                break;

            case '2' :
                disconnectFromServer(&socketFd, &connected);
                break;

            case '3' :
                //message to server
                std::cout << "How much water? ";
                std::getline(std::cin, input);
                message = "&1;" + input + "#";
                sendMessageToServer(&socketFd, &connected, message);
                break;

            case '4' :
                //message to server
                std::cout << "Stop taking water";
                message = "&2#";
                sendMessageToServer(&socketFd, &connected, message);
                break;

            case '5' :
                //message to server
                std::cout << "How much power to heat? ";
                std::getline(std::cin, input);
                message = "&3;" + input + "#";
                sendMessageToServer(&socketFd, &connected, message);
                break;

            case '6' :
                //message to server
                std::cout << "Stop heating?";
                message = "&4#";
                sendMessageToServer(&socketFd, &connected, message);
                break;

            case '7' :
                //message to server
                message = "&5;0#";
                sendMessageToServer(&socketFd, &connected, message);
                break;

             case '8' :
                //message to server
                std::cout << "Response: ";
                std::getline(std::cin, input);
                message = "&7;" + input + "#";
                sendMessageToServer(&socketFd, &connected, message);
                break;

            case 'q' :
                quit = true;
                break;

            default:
                std::cout << "\n\nI did not understand your choice (" << choice << ")" << std::endl;
                break;
        }
    }
    socketThread.detach();
    return 0;
}