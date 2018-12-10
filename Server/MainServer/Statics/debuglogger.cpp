#include "debuglogger.h"

#include <fstream>

#include <sys/stat.h>

std::vector<DebugLogger::DebugLogstruct> DebugLogger::DebugLog;
bool DebugLogger::LiveDebugLogging;
std::string DebugLogger::basePath = "loggers/";

DebugLogger::DebugLogger()
{
    
}

/// <summary>
/// Writes a new line in the DebugLog.
/// <param name="errorMessage">The (hole) error.</param>
/// <param name="source">The source of the error.</param>
/// </summary>
void DebugLogger::Record(std::string errorMessage, std::string source)
{
   // current date/time based on current system
   time_t now = time(0);
   
   // convert now to string form
   char* dt = ctime(&now);

   // convert now to tm struct for UTC
   tm *gmtm = gmtime(&now);
   dt = asctime(gmtm);
   dt[24] = '\0';
   
    DebugLogstruct error = DebugLogstruct
    {
        errorMessage,
        source,
        dt
    };

    DebugLog.push_back(error);
    if(LiveDebugLogging) 
    {
        std::cout << "[" << error.time << "] Source: " << error.source << " -- " << error.message << "\n";
    }
}

/// <summary>
/// Displays the last 20 lines of the current DebugLog
/// </summary>
std::string DebugLogger::Display()
{
    std::string message;
    if (DebugLog.size() <= 20)
    {
        for(DebugLogstruct debug : DebugLog)
        {
            message += "[" + debug.time + "] Source: " + debug.source + " -- " + debug.message + "\n";
        }
        return message;
    }

    message += "[...] skipped " + (DebugLog.size() - 20);
    message += "lines\n";
    for (int i = DebugLog.size() - 20; i < 20; i++)
    {
        DebugLogstruct debug = DebugLog[i];
        message += "[" + debug.time + "] Source: " + debug.source + " -- " + debug.message + "\n";
    }
    return message;
}

/// <summary>
/// Save the DebugLog to a file.
/// </summary>
void DebugLogger::SaveAsFile()
{
    // current date/time based on current system
    time_t now = time(0);
    
    // convert now to string form
    char* dt = ctime(&now);

    // convert now to tm struct for UTC
    tm *gmtm = gmtime(&now);
    dt = asctime(gmtm);
    dt[24] = '\0';

    std::string cmd = "mkdir -p " + basePath;

    system(cmd.c_str());
   
    std::string filename = basePath + dt;

    std::ofstream errorFile (filename + ".txt");
    std::vector<DebugLogger::DebugLogstruct> DebugLogCopy(DebugLog);

    for(u_int i = 0; i < DebugLogCopy.size(); i++)
    {
        errorFile << DebugLogCopy[i].time + " Source: " + DebugLogCopy[i].source + " -- " + DebugLogCopy[i].message + '\n';
    }

    errorFile.close();
    std::cout << "File saved\n";
}