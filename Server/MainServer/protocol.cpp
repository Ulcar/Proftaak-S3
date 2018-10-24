#include "protocol.h"

std::string Protocol::ToClient(std::vector<std::string> message)
{
    std::string startChar = "#";
    std::string endChar = "&";

    std::string messageToClient = makeString(message, startChar, endChar);
    return messageToClient;
}

std::vector<std::string> Protocol::FromClient(std::string message)
{
    std::vector<std::string> vector;
    std::string startChar = "&";
    std::string endChar = "#";
    char splitChar = ';';

    if ((message.substr(0,1) == startChar) && (message.substr(message.length()-1 , 1) == endChar))
    {
        std::string text = message.substr(1, message.length() -2 );
        vector = SplitString(text, splitChar);
    }

    return vector;
}

std::string Protocol::ToInterface(std::vector<std::string> message)
{
    std::string startChar = "#";
    std::string endChar = "&";
    std::string messageToInterface = makeString(message, startChar, endChar);
    return messageToInterface;
}

std::vector<std::string> Protocol::FromInterface(std::string message)
{
    std::vector<std::string> vector;
    std::string startChar = "$";
    std::string endChar = "#";
    char splitChar = ';';

    if ((message.substr(0,1) == startChar) && (message.substr(message.length()-1 , 1) == endChar))
    {
        std::string text = message.substr(1, message.length() -2 );
        vector = SplitString(text, splitChar);
    }

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
