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

std::string Protocol::ToInterface(Code code, int value)
{
    std::string messageToInterface = MakeString(code, value, startCharToInterface, endCharToInterface);
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

std::vector<std::string> Protocol::SplitString(std::string text, char splitChar, char startChar, char endChar)
{
    std::vector<std::string> commando;

    if ((text.substr(0,1).at(0) == startChar) && (text.substr(text.length()-1 , 1).at(0) == endChar))
    {
        text = text.substr(1, text.length() -2 );
        text += " ";
        size_t prevIndex = 0;

        while(true)
        {
            size_t index = text.find_first_of(splitChar, prevIndex);
            if(index > text.length())
            {
                break;
            }
            std::string ff = text.substr(prevIndex, index - prevIndex);
            commando.push_back(ff);
            prevIndex = index + 1;
        }
    }
    return commando;
}
