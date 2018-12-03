#include "consoleHandler.h"


Database* ConsoleHandler::database;

void ConsoleHandler::RunConsoleHandler(Database* tempdatabase)
{
    database = tempdatabase;
    std::cout << "  Console started\n";

    while(true)
    {
        std::cout << "command:\n";
        std::string commando;
        std::getline(std::cin, commando);
        
        std::vector<std::string> commandos = Protocol::SplitString(commando, ' ');

        try
        {
            if ((commandos.at(0) == "exit") || (commandos.at(0) == "quit") || (commandos.at(0) == "q"))
            {
                database->SetQuit(true);
                return;
            }
            else if(commandos.at(0) == "errorlogger")
            {
                if(commandos.size() == 1)
                {
                    std::cout << "live\n";
                    std::cout << "save\n";
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
                        std::cout << "Live Errorlogging: " << Errorlogger::LiveErrorLogging << "\n";
                    }
                }
            }
            else if(commandos.at(0) == "ping")
            {
                std::cout << "Pong";
            }
            else
            {
                std::cout << "Invalid arg: " << commando << "\n";
            }
        }
        catch(std::exception)
        {
            std::cout << "Exception: " << commando << "/n";
        }
    }
}