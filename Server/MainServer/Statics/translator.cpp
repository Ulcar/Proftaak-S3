#include "translator.h"

std::string Translator::ToMachine(M_Code code, int value)
{
    std::vector<std::string> temp = {std::to_string(value)};
    std::string messageToMachine = MakeString(code, temp, startCharToMachine, endCharToMachine);
    return messageToMachine;
}

std::string Translator::ToMachine(M_Code code, std::vector<int> values)
{
    std::vector<std::string> temp;
    for(int value : values)
    {
        temp.push_back(std::to_string(value));
    }
    
    std::string messageToMachine = MakeString(code, temp, startCharToMachine, endCharToMachine);
    return messageToMachine;
}


std::vector<std::vector<std::string>> Translator::FromMachine(std::string message)
{
    return SplitString(message, seperatorChar, endCharToMachine, startCharToMachine);
}

std::string Translator::ToControlPanel(CP_Code code, std::vector<std::string> value)
{
    std::string messageToControlPanel = MakeString(code, value, startCharToControlPanel, endCharToControlPanel);
    return messageToControlPanel;
}

std::vector<std::vector<std::string>> Translator::FromControlPanel(std::string message)
{
    return SplitString(message, seperatorChar, endCharToControlPanel, startCharToControlPanel);
}

std::string Translator::MakeString(int code, std::vector<std::string> value, char startChar, char endChar)
{
    std::string newString;
    newString = startChar + std::to_string(code);

    for(std::string mess : value)
    {
        newString = newString + seperatorChar + mess;
    }
    newString += endChar;
    return newString;
}

std::vector<std::vector<std::string>> Translator::SplitString(std::string text, char splitChar, char startChar, char endChar)
{
    std::vector<std::vector<std::string>> buffer;
    while(text.size() > 0)
    {
        int indexStart = text.find_first_of(startChar);
        int indexEind = text.find_first_of(endChar);

        if((indexStart == -1) || (indexEind == -1))
            return buffer;

        std::string message = text.substr(startChar, endChar - startChar );
        buffer.push_back(SplitString(message, splitChar));
    }
    return buffer;
}

std::vector<std::string> Translator::SplitString(std::string text, char splitChar)
{
    std::vector<std::string> commando;

    size_t prevIndex = 0;

    while(true)
    {
        
        size_t index = text.find_first_of(splitChar, prevIndex);
        if((index > text.length()) || (index == std::string::npos))
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