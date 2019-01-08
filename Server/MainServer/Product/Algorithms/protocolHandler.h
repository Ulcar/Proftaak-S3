#ifndef PROTOCOLHANDLER_H
#define PROTOCOLHANDLER_H

#include "database.h"
#include "consoleHandler.h"
#include "iAlgorithm.h"
#include "client.h"
#include "machine.h"

class ProtocolHandler
{
    public:
        ProtocolHandler(Database* database);
        ~ProtocolHandler();
        void HandleMessages();

    private:
        Database* database;

        void HandleControlPanel(Client* client, std::vector<std::string> messageVector, std::vector<Client*> clients);
        void HandleWasmachine(Machine* machine, std::vector<std::string> messageVector);
        void HandleStomer(Machine* machine, std::vector<std::string> messageVector);
        void UpdateLaundryBaskets();
};

#endif