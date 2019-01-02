#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "database.h"
#include "consoleHandler.h"
#include "iAlgorithm.h"
#include "client.h"
#include "machine.h"

class Algorithm
{
    public:
        Algorithm(Database* database, iAlgorithm* algorithm);
        ~Algorithm();
        void HandleMessages();

    private:
        Database* database;
        iAlgorithm* algorithm;

        void HandleControlPanel(Client* client, std::vector<std::string> messageVector, std::vector<Client*> clients);
        void HandleWasmachine(Machine* machine, std::vector<std::string> messageVector);
        void HandleStomer(Machine* machine, std::vector<std::string> messageVector);
};

#endif