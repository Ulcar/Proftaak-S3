#include "protocol.h"

std::string Protocol::ToMachine(M_Code code, int value)
{
    std::string messageToMachine = MakeString(code, value + "", startCharToMachine, endCharToMachine);
    return messageToMachine;
}

std::vector<std::string> Protocol::FromMachine(std::string message)
{
    return SplitString(message, seperatorChar, endCharToMachine, startCharToMachine);
}

std::string Protocol::ToControlPanel(CP_Code code, std::string value)
{
    std::string messageToControlPanel = MakeString(code, value, startCharToControlPanel, endCharToControlPanel);
    return messageToControlPanel;
}

std::vector<std::string> Protocol::FromControlPanel(std::string message)
{
    return SplitString(message, seperatorChar, endCharToControlPanel, startCharToControlPanel);
}

std::string Protocol::MakeString(int code, std::string value, char startChar, char endChar)
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