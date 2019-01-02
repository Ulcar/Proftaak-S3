#ifndef ALGORITHM_EASY_H
#define ALGORITHM_EASY_H

#include "iAlgorithm.h"
#include "database.h"
#include "consoleHandler.h"
#include "client.h"
#include "machine.h"

class Algorithm_easy : public iAlgorithm
{
    public:
        Algorithm_easy(Database* database);
        ~Algorithm_easy();
        
        void HandleControlPanelConsole(Client* client, std::vector<std::string> messageVector);
        void HandleControlPanelGetClients(Client* client, std::vector<std::string> messageVector, std::vector<Client*> clients);
        void HandleControlPanelTotalWater(Client* client, std::vector<std::string> messageVector);
        void HandleControlPanelTotalPower(Client* client, std::vector<std::string> messageVector);
        void HandleControlPanelDisableAllClients(Client* client, std::vector<std::string> messageVector, std::vector<Client*> clients);
        void HandleControlPanelSetClient(Client* client, std::vector<std::string> messageVector);
        void HandleWasmachineHeater(Machine* machine, std::vector<std::string> messageVector);
        void HandleWasmachineWater(Machine* machine, std::vector<std::string> messageVector);
        void HandleWasmachineDone(Machine* machine, std::vector<std::string> messageVector);
        void HandleStomerHeater(Machine* machine, std::vector<std::string> messageVector);
        void HandleStomerWater(Machine* machine, std::vector<std::string> messageVector);
        void HandleStomerDone(Machine* machine, std::vector<std::string> messageVector);

    private:
        Database* database;
};

#endif