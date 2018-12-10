#include "consoleHandler.h"


Database* ConsoleHandler::database;

void ConsoleHandler::RunConsoleHandler(Database* tempdatabase)
{
    database = tempdatabase;
    DebugLogger::Record("Console started", "consoleHandler");

    while(true)
    {
        std::cout << "command:\n";
        std::string commando;
        std::getline(std::cin, commando);

        std::cout << HandleConsoleCommando(commando);
    }
}

std::string ConsoleHandler::HandleConsoleCommando(std::string commando)
{  
    std::string message;
    std::vector<std::string> commandos = Protocol::SplitString(commando, ' ');

    try
    {
        if ((commandos.at(0) == "exit") || (commandos.at(0) == "quit") || (commandos.at(0) == "q"))
        {
            database->SetQuit(true);
            return;
        }
        else if((commandos.at(0) == "errorlogger") || (commandos.at(0) == "el"))
        {
            if(commandos.size() == 1)
            {
                message += "display\n";
                message += "live\n";
                message += "save\n";
            }
            else
            {
                if(commandos.at(1) == "save")
                {
                    Errorlogger::SaveAsFile();
                }
                else if(commandos.at(1) == "live")
                {
                    Errorlogger::LiveErrorLogging = !Errorlogger::LiveErrorLogging;
                    message += "Live Errorlogging: " + Errorlogger::LiveErrorLogging;
                    message += "\n";
                }
                else if(commandos.at(1) == "display")
                {
                    message += Errorlogger::Display();
                }
            }
        }
        else if((commandos.at(0) == "debuglogger") || (commandos.at(0) == "dl"))
        {
            if(commandos.size() == 1)
            {
                message += "display\n";
                message += "live\n";
                message += "save\n";
            }
            else
            {
                if(commandos.at(1) == "save")
                {
                    DebugLogger::SaveAsFile();
                }
                else if(commandos.at(1) == "live")
                {
                    DebugLogger::LiveDebugLogging = !DebugLogger::LiveDebugLogging;
                    message += "Live Debuglogging: " + DebugLogger::LiveDebugLogging;
                    message += "\n";
                }
                else if(commandos.at(1) == "display")
                {
                    message += DebugLogger::Display();
                }
            }
        }
        else if(commandos.at(0) == "ping")
        {
            message += "Pong";
        }
        else
        {
            message += "Invalid arg: " + commando + "\n";
        }
    }
    catch(std::exception)
    {
        Errorlogger::Record("Exception in handling command: " + commando, "consoleHandler");
        message += "Exception: " + commando + "/n";
    }
    return message;
}