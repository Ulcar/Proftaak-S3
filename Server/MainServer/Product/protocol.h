#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "codes.h"

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
        static std::string ToClient(Code code, int value);
        static std::vector<std::string> FromClient(std::string);
        static std::string ToInterface(Code code, int value);
        static std::vector<std::string> FromInterface(std::string);
        static std::vector<std::string> Protocol::SplitString(std::string text, char splitChar);

    private:
        static const char startCharToClient = '#';
        static const char endCharToClient = '&';
        static const char startCharToInterface = '#';
        static const char endCharToInterface = '$';
        static const char seperatorChar = ':';
        static const int port = 2018; //set port here
        static std::string MakeString(int code, int value, char startChar, char endChar);
        static std::vector<std::string> Protocol::SplitString(std::string text, char splitChar, char startChar, char endChar);

};

#endif

