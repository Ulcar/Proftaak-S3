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
    std::string startChar = "#";
    std::string endChar = "&";
    std::string messageToClient = makeString(message, startChar, endChar);
    return messageToClient;
}

std::vector<std::string> Protocol::FromClient(std::string)
{

}

std::string Protocol::ToInterface(std::vector<std::string> message)
{
    std::string startChar = "#";
    std::string endChar = "&";
    std::string messageToInterface = makeString(message, startChar, endChar);
    return messageToInterface;
}

std::vector<std::string> Protocol::FromInterface(std::string)
{

}

std::string Protocol::makeString(std::vector<std::string> message, std::string startChar, std::string endChar)
{
    std::string newString;
    newString = startChar;
    for(int i = 0; i < message.size(); i++)
    {
        if(i != 0)
        {
            newString += ";";
        }
        newString += message[i];

    }
    newString += endChar;
    return newString;
}
