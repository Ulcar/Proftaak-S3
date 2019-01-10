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
                if((commandos.at(1) == "save") || (commandos.at(1) == "s"))
                {
                    Logger::SaveErrorAsFile();
                }
                else if((commandos.at(1) == "live") || (commandos.at(1) == "l"))
                {
                    Logger::LiveErrorLogging = !Logger::LiveErrorLogging;
                    message += "Live Errorlogging: " + Logger::LiveErrorLogging;
                    message += "\n";
                }
                else if((commandos.at(1) == "display") || (commandos.at(1) == "d"))
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
                if((commandos.at(1) == "save") || (commandos.at(1) == "s"))
                {
                    Logger::SaveDebugAsFile();
                }
                else if((commandos.at(1) == "live") || (commandos.at(1) == "l"))
                {
                    Logger::LiveDebugLogging = !Logger::LiveDebugLogging;
                    message += "Live Debuglogging: " + Logger::LiveDebugLogging;
                    message += "\n";
                }
                else if((commandos.at(1) == "display") || (commandos.at(1) == "d"))
                {
                    message += Logger::DisplayDebugLog();
                }
            }
        }
        else if((commandos.at(0) == "ping") || (commandos.at(0) == "p"))
        {
            message += "Pong\n";
        }
        else if((commandos.at(0) == "laundry") || (commandos.at(0) == "l"))
        {
            Laundry* laundry = new Laundry(stoi(commandos.at(1)));
            laundry->ColorType = static_cast<Color>(stoi(commandos.at(2)));
            for(uint i = 3; i < commandos.size(); i++)
            {
                laundry->TasksToDo.push_back(static_cast<Type>(stoi(commandos.at(i))));
            }
            database->AddLaundry(laundry);
        }
        else if((commandos.at(0) == "clear") || (commandos.at(0) == "c") || (commandos.at(0) == "clr"))
        {
            message += "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            Logger::Record(false, "Cleared terminalscreen", "ConsoleHandler");
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