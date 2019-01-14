#include "protocolHandler.h"

Database* ProtocolHandler::database;
std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration> ProtocolHandler::start_time;
std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration> ProtocolHandler::current_time;

void ProtocolHandler::RunProtocolHandler(Database* tempDatabase)
{
    // startTime = std::chrono::system_clock::now();
    database = tempDatabase;
    start_time = std::chrono::steady_clock::now();
    Logger::Record(false, "Protocol started", "protocolHandler");

    while(true)
    {
        Update();
    }
}

void ProtocolHandler::Update()
{
    ProtocolHandler::HandleMessages();
    database->HandleLaundry();
    database->HandleLaundryBaskets();
  
            current_time = std::chrono::steady_clock::now();
        auto delta_time =   std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count();
        if(delta_time >= 2)
            {
            
    //  Logger::Record(false, "two seconds passed!!!!!", "ProtocolHandler");
      std::vector<Client*> clients = database->GetClients();
      
      for(Client* client : clients)
      {
          if(client->GetType() != Type::ControlPanel && client->IsEnabled() && client->GetSocket() != nullptr)
          {
              Machine* machine = (Machine*)client;
              machine->Send(M_CODE_HEARTBEAT, 0);
              machine->AddToReplyCount();
              if(machine->GetReplyCount() > 5)
              {
                  Logger::Record(false, "Machine timed out: " + machine->GetMacAdress(), "ProtocolHandler");
                  machine->SetSocket(nullptr);
              }

          }
      }
      start_time = std::chrono::steady_clock::now();
  }
}

    
    //currentTime = std::chrono::system_clock::now();
 
  //std::chrono::duration<std::chrono::seconds> seconds =   std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);

void ProtocolHandler::HeartbeatClient(Client* client)
{
    if(client->GetType() != Type::ControlPanel && client->IsEnabled() && client->GetSocket() != nullptr)
    {
        Machine* machine = (Machine*)client;
        machine->Send(M_CODE_HEARTBEAT, 0);
        machine->AddToReplyCount();
        if(machine->GetReplyCount() > 5)
        {
            Logger::Record(false, "Machine timed out: " + machine->GetMacAdress(), "ProtocolHandler");
            machine->SetSocket(nullptr);
        }

    } 
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
            continue;
        }

        //handle message:
        switch(client->GetType())
        {
            case Type::ControlPanel:
            {
                std::vector<std::vector<std::string>> messageVector = Translator::FromControlPanel(message);
                
                for(size_t i = 0; i < messageVector.size(); i++)
                {
                    HandleControlPanel(client, messageVector.at(i), tempClients);
                }
                break;
            }
            case Type::Wasmachine:
            {
                Machine* machine = dynamic_cast<Machine*>(client);
                std::vector<std::vector<std::string>> messageVector = Translator::FromMachine(message);
                
                for(size_t i = 0; i < messageVector.size(); i++)
                {
                    HandleWasmachine(machine, messageVector.at(i));
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

void ProtocolHandler::HandleControlPanel(Client* client, std::vector<std::string> messageVector, std::vector<Client*> clients)
{
    try
    {
        switch(static_cast<CP_Code>(stoi(messageVector[0])))
        {
            case CP_CODE_CONSOLE:
            {
                client->Send(CP_CODE_CONSOLE, ConsoleHandler::HandleConsoleCommando(messageVector[1]));           
                break;
            }

            case CP_CODE_GETCLIENTS: 
            {
                for(Client* tmpClient : clients)
                {
                    if(tmpClient->GetType() == Type::Wasmachine)
                    {
                        Machine* machine = (Machine*)tmpClient;
                        //send water, power, program and macAdress
                        std::vector<std::string> tmp;
                        tmp.push_back(machine->GetMacAdress());
                        tmp.push_back(std::to_string(machine->GetUsedWater()));
                        tmp.push_back(std::to_string(machine->GetUsedPower()));
                        tmp.push_back(std::to_string(machine->GetProgram()));
                        tmp.push_back(std::to_string(machine->IsEnabled()));
                        client->Send(CP_CODE_GETCLIENTS, tmp) ;
                    }
                }
                break;
            }

            case CP_CODE_TOTALWATER:
            {
                client->Send(CP_CODE_TOTALWATER, std::to_string(database->AskCurrentWater()));
                break;
            }

            case CP_CODE_TOTALPOWER:
            {
                client->Send(CP_CODE_TOTALPOWER, std::to_string(database->AskCurrentPower()));
                break;
            }

            case CP_CODE_DISABLEALLCLIENTS:
            {
                for(Client* tmpClient : clients)
                {
                    if(tmpClient->GetType() != Type::ControlPanel)
                    {
                        tmpClient->SetEnable(false);
                    }
                }
                break;
            }

            case CP_CODE_SETCLIENT:
            {
                for(Client* tmpClient : clients)
                {
                    if((tmpClient->GetType() != Type::ControlPanel) && (tmpClient->GetMacAdress() == messageVector[1]))
                    {
                        tmpClient->SetEnable(stoi(messageVector[2]));

                        Machine* machine = (Machine*)tmpClient;
                        //send macAdress, water, power, program and enabled
                        std::vector<std::string> tmp;
                        tmp.push_back(machine->GetMacAdress());
                        tmp.push_back(std::to_string(machine->GetUsedWater()));
                        tmp.push_back(std::to_string(machine->GetUsedPower()));
                        tmp.push_back(std::to_string(machine->GetProgram()));
                        tmp.push_back(std::to_string(machine->IsEnabled()));
                        client->Send(CP_CODE_GETCLIENTS, tmp) ;
                    }
                }
                break;
            }

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
        {
            if(database->UpdatePower(stoi(messageVector[1])))
            {
                machine->SetUsedPower(stoi(messageVector[1]));
                machine->Send(M_CODE_REQUEST_HEATER, 0);
                return;
            }
            machine->Send(M_CODE_REQUEST_HEATER, 1);
            break;
        }  

        case M_CODE_STOP_HEATER:
        {
            int amount = machine->GetUsedPower();
            database->ResetPower(amount);
            machine->SetUsedPower(0);
            machine->Send(M_CODE_STOP_HEATER, 0);
            break;
        }

        case M_CODE_REQUEST_WATER: 
        {
            if(database->UpdateWater(stoi(messageVector[1])))
            {
                machine->SetUsedWater(stoi(messageVector[1]));
                machine->Send(M_CODE_REQUEST_WATER, 0);
                return;
            }
            machine->Send(M_CODE_REQUEST_WATER, 1);
            break;
        }

        case M_CODE_STOP_WATER:
        {
            int amount = machine->GetUsedWater();
            database->ResetWater(amount);
            machine->SetUsedWater(0);
            machine->Send(M_CODE_STOP_WATER, 0);
            break;
        }

        case M_CODE_DONE:
        {
            Logger::Record(false, "Wasmachine " + machine->GetMacAdress() + " is done with " + std::to_string(machine->GetProgram()),"ProtocolHandler");
            machine->SetProgram(Program::PROGRAM_NONE); 
            break;
        }

        case M_CODE_HEARTBEAT:
            machine->ResetReplyCount();
            break;
            

        case M_CODE_SENDPROGRAM:
            if(machine->IsRequestingInProgress())
            {
                if(stoi(messageVector[1]) == 0)
                {
                    machine->SetRequestingInProgress(false);
                    machine->SetInProgress(true);
                     Logger::Record(false, "Wasmachine " + machine->GetMacAdress() + " is In progress on" + std::to_string(machine->GetProgram()),"ProtocolHandler");
                }

                else
                {
                    for(LaundryBasket* laundry : database->GetLaundryBaskets())
                    {
                        if(machine->GetMacAdress() == laundry->GetMacAdress())
                        {
                            Logger::Record(true, "Wasmachine " + machine->GetMacAdress() + "Gave an error on: " + std::to_string(machine->GetProgram()),"ProtocolHandler");
                            laundry->SetBusy(false);
                            machine->SetRequestingInProgress(false);
                        }
                    }
                }
            }
            else
            {
                Logger::Record(true, "Machine" + machine->GetMacAdress() + "Is Responding a SendProgram when we're not requesting it?","ProtocolHandler");
            }
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
        {
            if(database->UpdatePower(stoi(messageVector[1])))
            {
                machine->SetUsedPower(stoi(messageVector[1]));
                machine->Send(M_CODE_REQUEST_HEATER, 1);
                return;
            }
            machine->Send(M_CODE_REQUEST_HEATER, 0);
            break;
        }

        case M_CODE_STOP_HEATER:
        {
            int amount = machine->GetUsedPower();
            database->ResetPower(amount);
            machine->SetUsedPower(0);
            machine->Send(M_CODE_STOP_HEATER, 1);
            break;
        }

        case M_CODE_REQUEST_WATER:
        {
            if(database->UpdateWater(stoi(messageVector[1])))
            {
                machine->SetUsedWater(stoi(messageVector[1]));
                machine->Send(M_CODE_REQUEST_WATER, 1);
                database->HandleLaundryFinish(machine->GetMacAdress());
                return;
            }
            machine->Send(M_CODE_REQUEST_WATER, 0);
            break;
        }

        case M_CODE_STOP_WATER:
        {
            int amount = machine->GetUsedWater();
            database->ResetWater(amount);
            machine->SetUsedWater(0);
            machine->Send(M_CODE_STOP_WATER, 1);
            break;
        }

        case M_CODE_DONE:
        {
            Logger::Record(false, "Stomer " + machine->GetMacAdress() + " is done with " + std::to_string(machine->GetProgram()),"ProtocolHandler");
            machine->SetProgram(Program::PROGRAM_NONE);   
            break;
        }

        default:
            break;
    }
}
