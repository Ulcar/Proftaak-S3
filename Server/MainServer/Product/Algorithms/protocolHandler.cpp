#include "protocolHandler.h"

ProtocolHandler::ProtocolHandler(Database* database)
    : database(database)
{
    
}

ProtocolHandler::~ProtocolHandler()
{
    
}

void ProtocolHandler::HandleMessages()
{
    std::vector<Client*> tempClients = database->GetClients();
    for(Client* client : tempClients)
    {
        Socket* tmpSock = client->GetSocket();
        if(tmpSock == nullptr)
        {
            continue;
        }
        std::string message = tmpSock->ReadLastMessage();
        if(message.empty())
        {
            return;
        }

        //handle message:
        switch(client->GetType())
        {
            case Type::ControlPanel:
            {
                std::vector<std::string> messageVector = Translator::FromControlPanel(message);

                HandleControlPanel(client, messageVector, tempClients);
                break;
            }
            case Type::Wasmachine:
            {
                Machine* machine = dynamic_cast<Machine*>(client);
                std::vector<std::string> messageVector = Translator::FromMachine(message);

                HandleWasmachine(machine, messageVector);
                break;
            }
            default:
            {
                break;
            }
        }
    }
}

void ProtocolHandler::HandleControlPanel(Client* client, std::vector<std::string> messageVector, std::vector<Client*> clients)
{
    try
    {
        switch(static_cast<CP_Code>(stoi(messageVector[0])))
        {
            case CP_CODE_CONSOLE:
                client->Send(CP_CODE_CONSOLE, ConsoleHandler::HandleConsoleCommando(messageVector[1]));           
                break;

            case CP_CODE_GETCLIENTS: 
                for(Client* client : clients)
                {
                    client->Send(CP_CODE_GETCLIENTS, clients.size() + "");
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
                client->Send(CP_CODE_TOTALPOWER, std::to_string(database->AskCurrentPower()));
                break;

            case CP_CODE_DISABLEALLCLIENTS:
                for(Client* client : clients)
                {
                    if(client->GetType() != Type::ControlPanel)
                    {
                        client->SetEnable(false);
                    }
                }
                break;

            case CP_CODE_SETCLIENT:
                //Maken van indefier om te weten enabled moet worden.
                // we need a disable client protocol message lole
                //client->SetEnable(true);
                break;

            default:
                break;
        }
    }
    catch(const std::bad_cast& e)
    {
        Logger::Record(true, "Start of message doesn't contain an int, or is out of range of the enum", "ProtocolHandler");
    }
}

void ProtocolHandler::HandleWasmachine(Machine* machine, std::vector<std::string> messageVector)
{
    switch(static_cast<M_Code>(stoi(messageVector[0])))
    {
        case M_CODE_REQUEST_HEATER:
            if(database->UpdatePower(stoi(messageVector[1])))
            {
                machine->SetUsedPower(stoi(messageVector[1]));
                machine->Send(M_CODE_REQUEST_HEATER, 1);
                return;
            }
            machine->Send(M_CODE_REQUEST_HEATER, 0);
            break;

        case M_CODE_STOP_HEATER:
            break;

        case M_CODE_REQUEST_WATER:  
            if(database->UpdateWater(stoi(messageVector[1])))
            {
                machine->SetUsedWater(stoi(messageVector[1]));
                machine->Send(M_CODE_REQUEST_WATER, 1);
                return;
            }
            machine->Send(M_CODE_REQUEST_WATER, 0);
            break;

        case M_CODE_STOP_WATER:
            break;

        case M_CODE_DONE:
            Logger::Record(false, "Wasmachine " + machine->GetMacAdress() + " is done with " + std::to_string(machine->GetProgram()), "Algorithm");
            machine->SetProgram(Program::PROGRAM_NONE); 
            break;

        default:
            break;
    }
}

void ProtocolHandler::HandleStomer(Machine* machine, std::vector<std::string> messageVector)
{
    switch(static_cast<M_Code>(stoi(messageVector[0])))
    {
        case M_CODE_REQUEST_HEATER:
            if(database->UpdatePower(stoi(messageVector[1])))
            {
                machine->SetUsedPower(stoi(messageVector[1]));
                machine->Send(M_CODE_REQUEST_HEATER, 1);
                return;
            }
            machine->Send(M_CODE_REQUEST_HEATER, 0);
            break;

        case M_CODE_STOP_HEATER:
            break;

        case M_CODE_REQUEST_WATER:
            if(database->UpdateWater(stoi(messageVector[1])))
            {
                machine->SetUsedWater(stoi(messageVector[1]));
                machine->Send(M_CODE_REQUEST_WATER, 1);
                database->HandleWashFinish(machine->GetMacAdress());
                return;
            }
            machine->Send(M_CODE_REQUEST_WATER, 0);
            break;

        case M_CODE_STOP_WATER:
            break;

        case M_CODE_DONE:
            Logger::Record(false, "Stomer " + machine->GetMacAdress() + " is done with " + std::to_string(machine->GetProgram()), "Algorithm");
            machine->SetProgram(Program::PROGRAM_NONE);   
            break;

        default:
            break;
    }
}