#ifndef LOGGER_H
#define LOGGER_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <vector>

class Logger
{
    public:
        Logger();
        ~Logger();

        static bool LiveDebugLogging;
        static bool LiveErrorLogging;
        static void Record(bool isError, std::string errorMessage, std::string source);
        static std::string DisplayErrorLog();
        static std::string DisplayDebugLog();
        static void SaveErrorAsFile();
        static void SaveDebugAsFile();

    private:
        struct Logstruct
        {
            std::string message;
            std::string source;
            std::string time;
        };

        static std::vector<Logstruct> DebugLog;
        static std::vector<Logstruct> ErrorLog;
        static std::string basePath;
};

#endif