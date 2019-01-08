#ifndef ERRORLOGGER_H
#define ERRORLOGGER_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <vector>

class Errorlogger
{
    public:
        Errorlogger();
        ~Errorlogger();

        static bool LiveErrorLogging;
        static void Record(std::string errorMessage, std::string source);
        static std::string Display();
        static void SaveAsFile();

    private:
        struct  ErrorLogstruct
        {
            std::string message;
            std::string source;
            std::string time;
        };

        static std::vector<ErrorLogstruct> ErrorLog;
        static std::string basePath;
};

#endif