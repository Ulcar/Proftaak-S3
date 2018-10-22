#include "protocol.h"

 std::string   Protocol::ToServer(std::vector<std::string> message)
{
    std::string startChar = "&";
    std::string endChar = "#";
    std::string messageToServer = makeString(message, startChar, endChar);
    return messageToServer;
}

 std::string   Protocol::ToServer(std::string message)
{
    std::string startChar = "&";
    std::string endChar = "#";
    std::string messageToServer = makeString(message, startChar, endChar);
    return messageToServer;
}

std::vector<std::string> Protocol::FromServer(std::string message)
{
std::vector<std::string> vector = SplitString(message, ';');
return vector;
}

std::vector<std::string> Protocol::SplitString(std::string text, char split)
{
    text += " ";
    std::vector<std::string> commando;
    size_t prevIndex = 0;

    while(true)
    {
        size_t index = text.find_first_of(split, prevIndex);
        if(index > text.length())
        {
            break;
        }
        std::string ff = text.substr(prevIndex, index - prevIndex);
        commando.push_back(ff);
        prevIndex = index + 1;
    }

    return commando;
}



std::string Protocol::makeString(std::vector<std::string> message, std::string startChar, std::string endChar)
{
    std::string newString;
    newString = startChar;
    for(size_t i = 0; i < message.size(); i++)
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

std::string Protocol::makeString(std::string message, std::string startChar, std::string endChar)
{
    std::string newString;
    newString = startChar;
    for(size_t i = 0; i < message.size(); i++)
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

