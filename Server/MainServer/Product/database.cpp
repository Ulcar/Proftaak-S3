#include "database.h"

Database::Database()
{

}

std::vector<Machine*> Database::GetMachines()
{
    std::unique_lock<std::mutex> lock (mtxMachine);
    return machines;
}

void Database::AddMachine(Machine* machine)
{
    std::unique_lock<std::mutex> lock (mtxMachine);
    machines.push_back(machine);
}


std::vector<ControlPanel*> Database::GetControlPanels()
{
    std::unique_lock<std::mutex> lock (mtxControl);
    return controlpanels;
}

void Database::AddControlPanel(ControlPanel* controlpanel)
{
    std::unique_lock<std::mutex> lock (mtxControl);
    controlpanels.push_back(controlpanel);
}