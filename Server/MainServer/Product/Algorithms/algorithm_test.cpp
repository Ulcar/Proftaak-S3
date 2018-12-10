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
        Type tmp = client->GetType();
        switch(tmp)
        {
            case Type::ControlPanel:{

                std::vector<std::string> messagevec = Protocol::FromInterface(message);

                switch(static_cast<Code>(stoi(messagevec[0])))
                {
                    case CODE_HEATER:
                        break;

                    default:
                        break;
                }
    
                break;
            }
            case Type::Wasmachine:{
                break;
            }
            default:
            {
                break;
            }
        }
    }
}