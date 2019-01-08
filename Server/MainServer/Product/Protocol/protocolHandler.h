#ifndef PROTOCOLHANDLER_H
#define PROTOCOLHANDLER_H

#include "client.h"
#include "consoleHandler.h"
#include "database.h"
#include "iAlgorithm.h"
#include "machine.h"
#include <chrono>

class ProtocolHandler
{
    public:
        ProtocolHandler(Database* database);
        ~ProtocolHandler();
        
        void Update();

    private:
        Database* database;

        void HandleControlPanel(Client* client, std::vector<std::string> messageVector, std::vector<Client*> clients);
        void HandleWasmachine(Machine* machine, std::vector<std::string> messageVector);
        void HandleStomer(Machine* machine, std::vector<std::string> messageVector);
        void HandleMessages();
        
     //   std::chrono::time_point startTime;
      //  std::chrono::time_point currentTime;
};

#endif