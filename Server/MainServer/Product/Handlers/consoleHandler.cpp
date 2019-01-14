#include "consoleHandler.h"


Database* ConsoleHandler::database;

void ConsoleHandler::RunConsoleHandler(Database* tempdatabase)
{
    database = tempdatabase;
    Logger::Record(false, "Console started", "consoleHandler");

    while (!database->AskQuit())
    {
        std::cout << "command:\n";
        std::string commando;
        std::getline(std::cin, commando);

        std::cout << HandleConsoleCommando(commando);
    }

    Logger::Record(false, "Console stopped", "consoleHandler");
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
                message += "heartbeat\n";
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
                else if((commandos.at(1) == "heartbeat") || (commandos.at(1) == "hb"))
                {
                    Logger::LiveHeartBeat = !Logger::LiveHeartBeat;
                    message += "Live HeartBeat: " + Logger::LiveHeartBeat;
                    message += "\n";
                }
            }
        }
        else if((commandos.at(0) == "ping") || (commandos.at(0) == "p"))
        {
            message += "Pong\n";
        }
        else if((commandos.at(0) == "laundry") || (commandos.at(0) == "l"))
        {
            if(commandos.size() == 1)
            {
                message += "add\n";
                message += "display\n";
            }
            if((commandos.at(1) == "add") || (commandos.at(1) == "a"))
            {
                if(commandos.size() >= 5)
                {
                    Laundry* laundry = new Laundry(stoi(commandos.at(2)), static_cast<Temperature>(stoi(commandos.at(3))),  static_cast<Color>(stoi(commandos.at(4))));
                    for(uint i = 5; i < commandos.size(); i++)
                    {
                        laundry->TasksToDo.push_back(static_cast<Type>(stoi(commandos.at(i))));
                    }
                    database->AddLaundry(laundry);
                    message += "Laundry added\n";
                }
                else
                {
                    message += "laundry add <kg> <id> <temperature> <color> <list machines>\n";
                }
            }
            else if((commandos.at(1) == "remove") || (commandos.at(1) == "r"))
            {
                if(commandos.size() == 3)
                {
                    for(LaundryBasket* basket : database->GetLaundryBaskets())
                    {
                        int i = 0;
                        std::vector<LaundryBasket*> tmpVector = basket->LaundryVector;
                                                
                        for(Laundry* laundry : tmpVector)
                        {
                            if(laundry->GetID() == std::stoi(commandos.at(2))
                            {
                                basket->LaundryVector.erase(LaundryVector.begin() + i);
                                i--;
                            }
                            i++;
                        }
                    }
                }
            }
            else if((commandos.at(1) == "display") || (commandos.at(1) == "d"))
            {
                for(LaundryBasket* basket : database->GetLaundryBaskets())
                {
                    for(Laundry* laundry : basket->LaundryVector)
                    {
                       message += "[" + std::to_string(basket->GetID()) + "] ID: " + std::to_string(laundry->GetID()) + ", " + std::to_string(laundry->temperature) + " *C, Color: " + std::to_string(laundry->ColorType) + "\n";
                    }
                }
            }
        }
        else if((commandos.at(0) == "clear") || (commandos.at(0) == "c") || (commandos.at(0) == "clr"))
        {
            message += "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
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