#include "algorithm_test.h"

Algorithm_test::Algorithm_test(Database* database)
    : database(database)
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