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
        static std::string ToMachine(M_Code code, int value);
        static std::vector<std::string> FromMachine(std::string);
        static std::string ToControlPanel(CP_Code code, std::vector<std::string> value);
        static std::vector<std::string> FromControlPanel(std::string);
        static std::vector<std::string> SplitString(std::string text, char splitChar);

    private:
        static const char startCharToMachine = '#';
        static const char endCharToMachine = '&';
        static const char startCharToControlPanel = '#';
        static const char endCharToControlPanel = '$';
        static const char seperatorChar = ';';
        static const int port = 2018; //set port here
        static std::string MakeString(int code, std::vector<std::string> value, char startChar, char endChar);
        static std::vector<std::string> SplitString(std::string text, char splitChar, char startChar, char endChar);

};

#endif