#include "consoleHandler.h"


Database* ConsoleHandler::database;

void ConsoleHandler::RunConsoleHandler(Database* tempdatabase)
{
    database = tempdatabase;
    Logger::Record(false, "Console started", "consoleHandler");

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
    std::vector<std::string> commandos = Translator::SplitString(commando, ' ');

    try
    {
        if ((commandos.at(0) == "exit") || (commandos.at(0) == "quit") || (commandos.at(0) == "q"))
        {
            database->SetQuit(true);
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
                    Logger::SaveErrorAsFile();
                }
                else if(commandos.at(1) == "live")
                {
                    Logger::LiveErrorLogging = !Logger::LiveErrorLogging;
                    message += "Live Errorlogging: " + Logger::LiveErrorLogging;
                    message += "\n";
                }
                else if(commandos.at(1) == "display")
                {
                    message += Logger::DisplayErrorLog();
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
                    Logger::SaveDebugAsFile();
                }
                else if(commandos.at(1) == "live")
                {
                    Logger::LiveDebugLogging = !Logger::LiveDebugLogging;
                    message += "Live Debuglogging: " + Logger::LiveDebugLogging;
                    message += "\n";
                }
                else if(commandos.at(1) == "display")
                {
                    message += Logger::DisplayDebugLog();
                }
            }
        }
        else if(commandos.at(0) == "ping")
        {
            message += "Pong\n";
        }
        else
        {
            message += "Invalid arg: " + commando + "\n";
        }
    }
    catch(std::exception)
    {
        Logger::Record(true, "Exception in handling command: " + commando, "consoleHandler");
        message += "Exception: " + commando + "/n";
    }
    return message;
}