#ifndef MACHINE_H
#define MACHINE_H

#include "client.h"

class Machine : public Client
{
    public:
        Machine(std::string macAdress, Type type);
        virtual ~Machine();
        void Send(M_Code code, int value);

        int GetUsedWater();
        void SetUsedWater(int setWater);
        int GetUsedPower();
        void SetUsedPower(int setPower);
        Program GetProgram();
        void SetProgram(Program SetProgram);

        bool IsInProgress();
        void SetInProgress(bool inProgress);

    private:
        int usedWater;
        int usedPower;
        Program currentProgram;
        bool inProgress;
};

#endif
