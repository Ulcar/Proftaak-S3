#ifndef MACHINE_H
#define MACHINE_H

#include "client.h"

class Machine : public Client
{
    public:
        Machine(std::string macAdress, Type type);
        ~Machine();

    private:
        
};

#endif