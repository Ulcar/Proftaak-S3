#include "protocol.h"

#include <arpa/inet.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <vector>

std::string Protocol::ToClient(std::vector<std::string> message)
{
    std::string ClientMessage = "";
    return ClientMessage;
}

std::vector<std::string> Protocol::FromClient(std::string)
{

}

std::string Protocol::ToInterface(std::vector<std::string> message)
{
    std::string InterfaceMessage = "";
    return InterfaceMessage;
}

std::vector<std::string> Protocol::FromInterface(std::string)
{

}


