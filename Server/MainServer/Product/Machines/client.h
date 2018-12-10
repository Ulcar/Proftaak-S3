#ifndef CLIENT_H
#define CLIENT_H

#include "enums.h"
#include "socket.h"
#include "codes.h"
#include "protocol.h"
#include "iClient.h"

#include <cstring>

class Client : public iClient
{
    public:
        Client(std::string macAdress, Type type);
        virtual ~Client();
        void Send(CP_Code code, std::vector<std::string> value);
        void Send(CP_Code code, std::string value);
        void SetSocket(Socket* socket);

        Socket* GetSocket()
        {
            return socket;
        }

        std::string GetMacAdress()
        {
            return macAdress;
        }

        Type GetType()
        {
            return clientType;
        }

    protected:
        const std::string macAdress;
        const Type clientType;
        Socket* socket;
};

#endif