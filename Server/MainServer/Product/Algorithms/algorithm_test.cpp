#include "algorithm_test.h"

Algorithm_test::Algorithm_test(Database* database)
{
    this->database = database;
}

Algorithm_test::~Algorithm_test()
{
    
}

void Algorithm_test::Beat()
{
    std::vector<Client*> tempClients = database->GetClients();
    for(Client* client : tempClients)
    {
        std::string message = client->GetSocket()->ReadLastMessage();
        if(message.empty())
        {
            return;
        }

        //handle message:
        switch(client->GetType())
        {
            case Type::ControlPanel:
            {
                std::vector<std::string> messagevec = Protocol::FromControlPanel(message);

                switch(static_cast<CP_Code>(stoi(messagevec[0])))
                {
                    case CP_CODE_CONSOLE:
                        client->Send(CP_CODE_CONSOLE, ConsoleHandler::HandleConsoleCommando(messagevec[1]));
                        break;

                    case CP_CODE_GETCLIENTS:
                        for(Client* client : tempClients)
                        {
                            client->Send(CP_CODE_GETCLIENTS, tempClients.size() + "");
                            if(client->GetType() == Type::Wasmachine)
                            {
                                Machine* machine = (Machine*)client;
                                //send water, power, program and macAdress
                                std::vector<std::string> tmp;
                                tmp.push_back(std::to_string(machine->GetUsedWater()));
                                tmp.push_back(std::to_string(machine->GetUsedPower()));
                                tmp.push_back(std::to_string(machine->GetProgram()));
                                tmp.push_back(machine->GetMacAdress());
                                client->Send(CP_CODE_GETCLIENTS, tmp) ;

                            }
                        }
                        break;

                    case CP_CODE_TOTALWATER:
                    client->Send(CP_CODE_TOTALWATER, std::to_string(database->AskCurrentWater()));
                    break;

                    case CP_CODE_TOTALPOWER:
                    client->Send(CP_CODE_TOTALWATER, std::to_string(database->AskCurrentPower()));
                    break;

                    
                    default:
                        break;
                }
    
                break;
            }
            case Type::Wasmachine:
            {
                std::vector<std::string> messagevec = Protocol::FromMachine(message);

                switch(static_cast<M_Code>(stoi(messagevec[0])))
                {
                    case M_CODE_HEATER:
                        break;

                    case M_CODE_WATER:
                        break;

                    case M_CODE_DONE:
                        break;

                    default:
                        break;
                }
                break;
            }
            default:
            {
                break;
            }
        }
    }
}