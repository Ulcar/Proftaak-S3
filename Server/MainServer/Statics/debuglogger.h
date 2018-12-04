#ifndef DEBUGLOGGER_H
#define DEBUGLOGGER_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <vector>

class DebugLogger
{
    public:
        DebugLogger();
        ~DebugLogger();

        static bool LiveDebugLogging;
        static void Record(std::string errorMessage, std::string source);
        static void Display();
        static void SaveAsFile();

    private:
        struct  DebugLogstruct
        {
            std::string message;
            std::string source;
            std::string time;
        };

        static std::vector<DebugLogstruct> DebugLog;
        static std::string basePath;
};

#endif