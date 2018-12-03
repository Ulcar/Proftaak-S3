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
    std::vector<Machine*> tempMachines = database->GetMachines();
    for(Machine* machine : tempMachines)
    {
        std::string message = machine->GetSocket()->ReadLastMessage();
        if(message.empty())
        {
            return;
        }

        //handle message
    }
}