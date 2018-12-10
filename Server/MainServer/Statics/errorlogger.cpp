#include "errorlogger.h"

#include <fstream>

#include <sys/stat.h>

std::vector<Errorlogger::ErrorLogstruct> Errorlogger::ErrorLog;
bool Errorlogger::LiveErrorLogging;
std::string Errorlogger::basePath = "loggers/";

Errorlogger::Errorlogger()
{
    
}

/// <summary>
/// Writes a new line in the Errorlog.
/// <param name="errorMessage">The (hole) error.</param>
/// <param name="source">The source of the error.</param>
/// </summary>
void Errorlogger::Record(std::string errorMessage, std::string source)
{
   // current date/time based on current system
   time_t now = time(0);
   
   // convert now to string form
   char* dt = ctime(&now);

   // convert now to tm struct for UTC
   tm *gmtm = gmtime(&now);
   dt = asctime(gmtm);
   dt[24] = '\0';
   
    ErrorLogstruct error = ErrorLogstruct
    {
        errorMessage,
        source,
        dt
    };

    ErrorLog.push_back(error);
    if(LiveErrorLogging) 
    {
        std::cout << "[" << error.time << "] Source: " << error.source << " -- " << error.message << "\n";
    }
}

/// <summary>
/// Displays the last 20 lines of the current Errorlog
/// </summary>
void Errorlogger::Display()
{
    if (ErrorLog.size() <= 20)
    {
        for(ErrorLogstruct error : ErrorLog)
        {
            std::cout << "[" << error.time << "] Source: " << error.source << " -- " << error.message << "\n";
        }
        return;
    }

    std::cout << "[...] skipped " << (ErrorLog.size() - 20) << "lines\n";
    for (int i = ErrorLog.size() - 20; i < 20; i++)
    {
        ErrorLogstruct error = ErrorLog[i];
        std::cout << "[" << error.time << "] Source: " << error.source << " -- " << error.message << "\n";
    }
}

/// <summary>
/// Save the Errorlog to a file.
/// </summary>
void Errorlogger::SaveAsFile()
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
    std::vector<Errorlogger::ErrorLogstruct> ErrorLogCopy(ErrorLog);

    for(u_int i = 0; i < ErrorLogCopy.size(); i++)
    {
        errorFile << ErrorLogCopy[i].time + " Source: " + ErrorLogCopy[i].source + " -- " + ErrorLogCopy[i].message + '\n';
    }

    errorFile.close();
    std::cout << "File saved\n";
}