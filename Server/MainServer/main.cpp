#include <iostream>
#include <vector>
//#include <thread> 

#include "client.h"
#include "socket.h"

//Client == Interface (C#)
//Socket = machines (C++)

bool quit;

        
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
    Socket* socket = new Socket();
    socket->Send();
    //std::thread inputThread (HandleUserInput); 
    std::cout << "------------------\n  Server started\n------------------\n";

    while(!quit){
        HandleUserInput();

    }

    std::cout << "\nServer Stopped...\n\n";
    
    return 0;
}