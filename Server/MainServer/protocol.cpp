#include "protocol.h"

std::string Protocol::ToClient(std::vector<std::string> message)
{
    std::string startChar = "#";
    std::string endChar = "&";
    std::string messageToClient = makeString(message, startChar, endChar);
    return messageToClient;
}

std::vector<std::string> Protocol::FromClient(std::string)
{
    std::vector<std::string> vector;
    return vector;
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
    std::vector<std::string> vector;
    return vector;
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

std::vector<std::string> Protocol::SplitString(std::string text, char split)
{
    text += " ";
    std::vector<std::string> commando;

    while(true)
    {
        size_t index = text.find_first_of(split, 0);
        if(index > text.length())
        {
            break;
        }
        std::string ff = text.substr(0, index);
        commando.push_back(text.substr(index + 1, text.length() - index));
    }

    return commando;
}
