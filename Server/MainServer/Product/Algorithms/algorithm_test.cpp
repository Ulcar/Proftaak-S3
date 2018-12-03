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
                break;
            case Type::Wasmachine:
                break;
        }
    }
}