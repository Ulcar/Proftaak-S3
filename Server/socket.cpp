#include "socket.h"
#include "enums.h"
#include <iostream>


Socket::Socket()
{
    ETA = 0;
    error = Error::None;
}

Socket::~Socket()
{

}

void Socket::Send()
{
    std::cout << "Succes\n";
}

int Socket::Ping()
{
    return 0;
}