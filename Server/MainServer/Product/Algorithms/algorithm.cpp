#include "algorithm.h"

Algorithm::Algorithm(Database* database, iAlgorithm* algorithm)
    : database(database)
    , algorithm(algorithm)
{
    
}

Algorithm::~Algorithm()
{
    
}

void Algorithm::HandleMessages()
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
                std::vector<std::string> messageVector = Protocol::FromControlPanel(message);

                HandleControlPanel(client, messageVector, tempClients);
                break;
            }
            case Type::Wasmachine:
            {
                Machine* machine = dynamic_cast<Machine*>(client);
                std::vector<std::string> messageVector = Protocol::FromMachine(message);

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

void Algorithm::HandleControlPanel(Client* client, std::vector<std::string> messageVector, std::vector<Client*> clients)
{
    try
    {
        switch(static_cast<CP_Code>(stoi(messageVector[0])))
        {
            case CP_CODE_CONSOLE:
                algorithm->HandleControlPanelConsole(client, messageVector);
                break;

            case CP_CODE_GETCLIENTS:
                algorithm->HandleControlPanelGetClients(client, messageVector, clients);
                break;

            case CP_CODE_TOTALWATER:
                algorithm->HandleControlPanelTotalWater(client, messageVector);
                break;

            case CP_CODE_TOTALPOWER:
                algorithm->HandleControlPanelTotalPower(client, messageVector);
                break;

            case CP_CODE_DISABLEALLCLIENTS:
                algorithm->HandleControlPanelDisableAllClients(client, messageVector, clients);
                break;

            case CP_CODE_SETCLIENT:
                algorithm->HandleControlPanelSetClient(client, messageVector);
                break;

            
            default:
                break;
        }
    }
    catch(const std::bad_cast& e)
    {
        Logger::Record(true, "Start of message doesn't contain an int, or is out of range of the enum", "Algorithm");
    }
}

void Algorithm::HandleWasmachine(Machine* machine, std::vector<std::string> messageVector)
{
    switch(static_cast<M_Code>(stoi(messageVector[0])))
    {
        case M_CODE_REQUEST_HEATER:
            algorithm->HandleWasmachineHeater(machine, messageVector);
            break;

        case M_CODE_STOP_HEATER:
            algorithm->HandleWasmachineHeater(machine, messageVector);
            break;

        case M_CODE_REQUEST_WATER:
            algorithm->HandleWasmachineWater(machine, messageVector);
            break;

        case M_CODE_STOP_WATER:
            algorithm->HandleWasmachineWater(machine, messageVector);
            break;

        case M_CODE_DONE:
            algorithm->HandleWasmachineDone(machine, messageVector);
            break;

        default:
            break;
    }
}

void Algorithm::HandleStomer(Machine* machine, std::vector<std::string> messageVector)
{
    switch(static_cast<M_Code>(stoi(messageVector[0])))
    {
        case M_CODE_REQUEST_HEATER:
            algorithm->HandleStomerHeater(machine, messageVector);
            break;

        case M_CODE_STOP_HEATER:
            algorithm->HandleStomerHeater(machine, messageVector);
            break;

        case M_CODE_REQUEST_WATER:
            algorithm->HandleStomerWater(machine, messageVector);
            break;

        case M_CODE_STOP_WATER:
            algorithm->HandleStomerWater(machine, messageVector);
            break;

        case M_CODE_DONE:
            algorithm->HandleStomerDone(machine, messageVector);
            break;

        default:
            break;
    }
}
