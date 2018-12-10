#include "protocol.h"

std::string Protocol::ToClient(Code code, int value)
{
    std::string messageToClient = MakeString(code, value, startCharToClient, endCharToClient);
    return messageToClient;
}

std::vector<std::string> Protocol::FromClient(std::string message)
{
    return SplitString(message, seperatorChar, endCharToClient, startCharToClient);
}

std::string Protocol::ToInterface(std::vector<std::string> message)
{
    std::string messageToInterface = MakeString(message, startCharToInterface, endCharToInterface);
    return messageToInterface;
}

std::vector<std::string> Protocol::FromInterface(std::string message)
{
    return SplitString(message, seperatorChar, endCharToInterface, startCharToInterface);
}

std::string Protocol::MakeString(int code, int value, char startChar, char endChar)
{
    std::string newString;
    newString = startChar;
    newString += code;
    newString += seperatorChar;
    newString += value;
    newString += endChar;
    return newString;
}

std::string Protocol::MakeString(std::vector<std::string> message, char startChar, char endChar)
{
    std::string newString;
    newString = startChar;
    newString += message.at(0);
    
    for(size_t i = 1; i < message.size(); i++)
    {
        newString += seperatorChar;
        newString += message.at(i);
    }
    newString += endChar;
    return newString;
}

std::vector<std::string> Protocol::SplitString(std::string text, char splitChar, char startChar, char endChar)
{
    if ((text.substr(0,1).at(0) == startChar) && (text.substr(text.length()-1 , 1).at(0) == endChar))
    {
        text = text.substr(1, text.length() -2 );
        return SplitString(text, splitChar);
    }
    std::vector<std::string> fu;
    return fu;
}

std::vector<std::string> Protocol::SplitString(std::string text, char splitChar)
{
    std::vector<std::string> commando;

    size_t prevIndex = 0;

    while(true)
    {
        size_t index = text.find_first_of(splitChar, prevIndex);
        if(index > text.length())
        {
            std::string ff = text.substr(prevIndex, text.length() - prevIndex);
            commando.push_back(ff);
            break;
        }
        std::string ff = text.substr(prevIndex, index - prevIndex);
        commando.push_back(ff);
        prevIndex = index + 1;
    }
    return commando;
}