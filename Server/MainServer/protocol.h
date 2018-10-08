#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <arpa/inet.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <vector>

class Protocol
{
    public:
        static int GetPort()
        {
            return port;
        }
        static std::string ToClient(std::vector<std::string> message);
        static std::vector<std::string> FromClient(std::string);
        static std::string ToInterface(std::vector<std::string> message);
        static std::vector<std::string> FromInterface(std::string);
        static std::vector<std::string> SplitString(std::string text, char split);

    private:
        static const int port = 2018; //set port here
        static std::string makeString(std::vector<std::string> message, std::string startChar, std::string endChar);

};

#endif

