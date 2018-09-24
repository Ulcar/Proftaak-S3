#include <iostream>
#include <vector>

#include "client.h"
#include "socket.h"


int main( void )
{  
    std::cout << "------------------\n  Server started\n------------------\n";
    Socket* socket = new Socket();

    socket->Send();
    std::cout << "\nServer Stopped...\n\n";
    
    return 0;
}