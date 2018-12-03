#ifndef DATABASE_H
#define DATABASE_H

#include "machine.h"
#include "socket.h"
#include "controlpanel.h"

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <mutex>
#include <unistd.h>
#include <vector>

class Database
{
    public:
        Database();
        std::vector<Machine*> GetMachines();
        void AddMachine(Machine* machine);
        std::vector<ControlPanel*> GetControlPanels();
        void AddControlPanel(ControlPanel* controlpanel);
        bool AskQuit();
        void SetQuit(bool quit);

    private:
        bool quit;
        std::vector<Socket*> sockets;
        std::vector<Machine*> machines;
        std::vector<ControlPanel*> controlpanels;

        std::mutex mtxMachine;
        std::mutex mtxControl;
        std::mutex mtxQuit;
};

#endif