#ifndef PROTOCOLHANDLER_H
#define PROTOCOLHANDLER_H

#include "client.h"
#include "consoleHandler.h"
#include "database.h"
#include "iAlgorithm.h"
#include "machine.h"
#include <chrono>

typedef std::chrono::duration<double, std::ratio<60>> MyMinuteTick;

class ProtocolHandler
{
    public:
        static void RunProtocolHandler(Database* tempDatabase);

    private:
        static Database* database;

        static void Update();
        static void HandleControlPanel(Client* client, std::vector<std::string> messageVector, std::vector<Client*> clients);
        static void HandleWasmachine(Machine* machine, std::vector<std::string> messageVector);
        static void HandleStomer(Machine* machine, std::vector<std::string> messageVector);
        static void HandleMessages();
        static void HeartbeatClient(Client* client);

        static std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration> start_time;
        static std::chrono::time_point<std::chrono::steady_clock, std::chrono::steady_clock::duration> current_time;
        
     //   std::chrono::time_point startTime;
      //  std::chrono::time_point currentTime;
};

#endif