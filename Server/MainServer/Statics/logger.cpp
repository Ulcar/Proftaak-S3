#include "logger.h"

#include <fstream>

#include <sys/stat.h>

std::vector<Logger::Logstruct> Logger::DebugLog;
std::vector<Logger::Logstruct> Logger::ErrorLog;
bool Logger::LiveDebugLogging;
bool Logger::LiveErrorLogging;
bool Logger::LiveHeartBeat;
std::string Logger::basePath = "loggers/";

Logger::Logger()
{
    
}

/// <summary>
/// Writes a new line in the DebugLog.
/// <param name="errorMessage">The (hole) error.</param>
/// <param name="source">The source of the error.</param>
/// </summary>
void Logger::Record(bool isError, std::string errorMessage, std::string source)
{
   // current date/time based on current system
   time_t now = time(0);
   
   // convert now to string form
   char* dt = ctime(&now);

   // convert now to tm struct for UTC
   tm *gmtm = gmtime(&now);
   dt = asctime(gmtm);
   dt[24] = '\0';
   
    Logstruct log = Logstruct
    {
        errorMessage,
        source,
        dt
    };

    if(isError)
    {
        ErrorLog.push_back(log);
        if(LiveErrorLogging) 
        {
            std::cout << "[" << log.time << "] Source: " << log.source << " -- " << log.message << "\n";
        }
    }
    else
    {
        DebugLog.push_back(log);
        int indexHeartBeat = log.message.find("#6;0&");
        if(LiveDebugLogging && (indexHeartBeat == -1)) 
        {
            std::cout << "[" << log.time << "] Source: " << log.source << " -- " << log.message << "\n";
        }
    }
}

/// <summary>
/// Displays the last 20 lines of the current ErrorLog
/// </summary>
std::string Logger::DisplayErrorLog()
{
    std::string message;
    if (ErrorLog.size() <= 20)
    {
        for(Logstruct log : ErrorLog)
        {
            message += "[" + log.time + "] Source: " + log.source + " -- " + log.message + "\n";
        }
        return message;
    }

    message += "[...] skipped " + (ErrorLog.size() - 20);
    message += "lines\n";
    for (int i = ErrorLog.size() - 20; i < 20; i++)
    {
        Logstruct log = ErrorLog[i];
        message += "[" + log.time + "] Source: " + log.source + " -- " + log.message + "\n";
    }
    return message;
}

/// <summary>
/// Displays the last 20 lines of the current DebugLog
/// </summary>
std::string Logger::DisplayDebugLog()
{
    std::string message;
    if (DebugLog.size() <= 20)
    {
        for(Logstruct debug : DebugLog)
        {
            message += "[" + debug.time + "] Source: " + debug.source + " -- " + debug.message + "\n";
        }
        return message;
    }

    message += "[...] skipped " + (DebugLog.size() - 20);
    message += "lines\n";
    for (int i = DebugLog.size() - 20; i < 20; i++)
    {
        Logstruct debug = DebugLog[i];
        message += "[" + debug.time + "] Source: " + debug.source + " -- " + debug.message + "\n";
    }
    return message;
}

/// <summary>
/// Save the ErrorLog to a file.
/// </summary>
void Logger::SaveErrorAsFile()
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
   
    std::string filename = basePath + dt + "-ErrorLog";

    std::ofstream errorFile (filename + ".txt");
    std::vector<Logger::Logstruct> ErrorLogCopy(ErrorLog);

    for(u_int i = 0; i < ErrorLogCopy.size(); i++)
    {
        errorFile << ErrorLogCopy[i].time + " Source: " + ErrorLogCopy[i].source + " -- " + ErrorLogCopy[i].message + '\n';
    }

    errorFile.close();
    std::cout << "Saved Errorlog\n";
}

/// <summary>
/// Save the DebugLog to a file.
/// </summary>
void Logger::SaveDebugAsFile()
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
   
    std::string filename = basePath + dt + "-DebugLog";

    std::ofstream debugFile (filename + ".txt");
    std::vector<Logger::Logstruct> DebugLogCopy(DebugLog);

    for(u_int i = 0; i < DebugLogCopy.size(); i++)
    {
        debugFile << DebugLogCopy[i].time + " Source: " + DebugLogCopy[i].source + " -- " + DebugLogCopy[i].message + '\n';
    }

    debugFile.close();
    std::cout << "Saved Debuglog\n";
}