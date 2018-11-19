#include "errorlogger.h"

#include <fstream>

std::vector<Errorlogger::ErrorLogstruct> Errorlogger::ErrorLog;
bool Errorlogger::LiveErrorLogging;

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


   std::string filename = dt;

std::ofstream errorFile (filename);

std::vector<Errorlogger::ErrorLogstruct> ErrorLogCopy(ErrorLog);

for(int i = 0; i < ErrorLog.size(); i++)
{
    errorFile << ErrorLog[i].time + " Source: " + ErrorLog[i].source + " -- " + ErrorLog[i].message + '\n';
}

errorFile.close();


/*
    Directory.CreateDirectory(basePath);
    StringBuilder sb = new StringBuilder();
    List<ErrorLogstruct> copyErrorLog = new List<ErrorLogstruct>(ErrorLog);
    string filename ="//" + DateTime.Now.Year + "-" + DateTime.Now.Month + "-" + DateTime.Now.Day + "_" + DateTime.Now.Hour + "-" + DateTime.Now.Minute + ".errorlog.txt";

    foreach (var error in copyErrorLog)
    {
        sb.AppendLine(String.Format("[{0}] Source: {2} -- {1}", error.time, error.source, error.message));
    }
    
    File.WriteAllText(basePath + filename, sb.ToString());
*/
    std::cout << "File saved\n";
}