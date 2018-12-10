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
void DebugLogger::Display()
{
    if (DebugLog.size() <= 20)
    {
        for(DebugLogstruct error : DebugLog)
        {
            std::cout << "[" << error.time << "] Source: " << error.source << " -- " << error.message << "\n";
        }
        return;
    }

    std::cout << "[...] skipped " << (DebugLog.size() - 20) << "lines\n";
    for (int i = DebugLog.size() - 20; i < 20; i++)
    {
        DebugLogstruct error = DebugLog[i];
        std::cout << "[" << error.time << "] Source: " << error.source << " -- " << error.message << "\n";
    }
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