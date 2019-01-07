#include "algorithm_easy.h"

Algorithm_easy::Algorithm_easy(Database* database)
    : database(database)
{
    
}

Algorithm_easy::~Algorithm_easy()
{
    
}

void Algorithm_easy::HandleControlPanelConsole(Client* client, std::vector<std::string> messageVector)
{
    client->Send(CP_CODE_CONSOLE, ConsoleHandler::HandleConsoleCommando(messageVector[1]));           
}

void Algorithm_easy::HandleControlPanelGetClients(Client* client, std::vector<std::string> messageVector, std::vector<Client*> clients)
{
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
}

void Algorithm_easy::HandleControlPanelTotalWater(Client* client, std::vector<std::string> messageVector)
{
    client->Send(CP_CODE_TOTALWATER, std::to_string(database->AskCurrentWater()));
}

void Algorithm_easy::HandleControlPanelTotalPower(Client* client, std::vector<std::string> messageVector)
{
    client->Send(CP_CODE_TOTALPOWER, std::to_string(database->AskCurrentPower()));
}

void Algorithm_easy::HandleControlPanelDisableAllClients(Client* client, std::vector<std::string> messageVector, std::vector<Client*> clients)
{
    for(Client* client : clients)
    {
        if(client->GetType() != Type::ControlPanel)
        {
            client->SetEnable(false);
        }
    }
}

void Algorithm_easy::HandleControlPanelSetClient(Client* client, std::vector<std::string> messageVector)
{
    //Maken van indefier om te weten enabled moet worden.
    // we need a disable client protocol message lole
    //client->SetEnable(true);
}



void Algorithm_easy::HandleWasmachineHeater(Machine* machine, std::vector<std::string> messageVector)
{
    if(database->UpdatePower(stoi(messageVector[1])))
    {
        machine->SetUsedPower(stoi(messageVector[1]));
        machine->Send(M_CODE_HEATER, 1);
        return;
    }
    machine->Send(M_CODE_HEATER, 0);
}

void Algorithm_easy::HandleWasmachineWater(Machine* machine, std::vector<std::string> messageVector)
{
    if(database->UpdateWater(stoi(messageVector[1])))
    {
        machine->SetUsedWater(stoi(messageVector[1]));
        machine->Send(M_CODE_WATER, 1);
        return;
    }
    machine->Send(M_CODE_WATER, 0);
}

void Algorithm_easy::HandleWasmachineDone(Machine* machine, std::vector<std::string> messageVector)
{
    DebugLogger::Record("Wasmachine " + machine->GetMacAdress() + " is done with " + std::to_string(machine->GetProgram()), "Algorithm");
    machine->SetProgram(Program::PROGRAM_NONE);        
}





void Algorithm_easy::HandleStomerHeater(Machine* machine, std::vector<std::string> messageVector)
{
    if(database->UpdatePower(stoi(messageVector[1])))
    {
        machine->SetUsedPower(stoi(messageVector[1]));
        machine->Send(M_CODE_HEATER, 1);
        return;
    }
    machine->Send(M_CODE_HEATER, 0);
}

void Algorithm_easy::HandleStomerWater(Machine* machine, std::vector<std::string> messageVector)
{
    if(database->UpdateWater(stoi(messageVector[1])))
    {
        machine->SetUsedWater(stoi(messageVector[1]));
        machine->Send(M_CODE_WATER, 1);
        return;
    }
    machine->Send(M_CODE_WATER, 0);
}

void Algorithm_easy::HandleStomerDone(Machine* machine, std::vector<std::string> messageVector)
{
    DebugLogger::Record("Stomer " + machine->GetMacAdress() + " is done with " + std::to_string(machine->GetProgram()), "Algorithm");
    machine->SetProgram(Program::PROGRAM_NONE);       
}

