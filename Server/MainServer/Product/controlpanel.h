#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include "socket.h"
#include "protocol.h"

class ControlPanel
{
    public:
        ControlPanel(std::string macAdress);
        ~ControlPanel();
        void Send(Code code, int value);
        void Read();
        int Ping();
        void Beat();
        void SetSocket(Socket* socket);

        Socket* GetSocket()
        {
            return socket;
        }

        std::string GetMacAdress()
        {
            return macAdress;
        }

    private:
        int error;
        const std::string macAdress;
        Socket* socket;
};

#endif