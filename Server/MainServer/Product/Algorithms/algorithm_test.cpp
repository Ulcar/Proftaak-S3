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
                std::vector<std::string> messagevec = Protocol::FromInterface(message);

                switch(static_cast<CP_Code>(stoi(messagevec[0])))
                {
                    case CP_CODE_CONSOLE:
                        break;

                    default:
                        break;
                }
    
                break;
            }
            case Type::Wasmachine:
            {
                std::vector<std::string> messagevec = Protocol::FromClient(message);

                switch(static_cast<CP_Code>(stoi(messagevec[0])))
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