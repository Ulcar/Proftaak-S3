#ifndef IALGORITHM_H
#define IALGORITHM_H

#include "client.h"
#include "machine.h"

#include <string>

class iAlgorithm
{
public:
    virtual void HandleControlPanelConsole(Client* client, std::vector<std::string> messageVector) = 0;
    virtual void HandleControlPanelGetClients(Client* client, std::vector<std::string> messageVector, std::vector<Client*> clients) = 0;
    virtual void HandleControlPanelTotalWater(Client* client, std::vector<std::string> messageVector) = 0;
    virtual void HandleControlPanelTotalPower(Client* client, std::vector<std::string> messageVector) = 0;
    virtual void HandleControlPanelDisableAllClients(Client* client, std::vector<std::string> messageVector, std::vector<Client*> clients) = 0;
    virtual void HandleControlPanelSetClient(Client* client, std::vector<std::string> messageVector) = 0;
    virtual void HandleWasmachineHeater(Machine* machine, std::vector<std::string> messageVector) = 0;
    virtual void HandleWasmachineWater(Machine* machine, std::vector<std::string> messageVector) = 0;
    virtual void HandleWasmachineDone(Machine* machine, std::vector<std::string> messageVector) = 0;
    virtual void HandleStomerHeater(Machine* machine, std::vector<std::string> messageVector) = 0;
    virtual void HandleStomerWater(Machine* machine, std::vector<std::string> messageVector) = 0;
    virtual void HandleStomerDone(Machine* machine, std::vector<std::string> messageVector) = 0;
};

#endif
