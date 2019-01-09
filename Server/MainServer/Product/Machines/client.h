#ifndef CLIENT_H
#define CLIENT_H

#include "codes.h"
#include "enums.h"
#include "iClient.h"
#include "socket.h"
#include "translator.h"

#include <cstring>

class Client : public iClient
{
    public:
        Client(std::string macAdress, Type type);
        virtual ~Client();
        void Send(CP_Code code, std::vector<std::string> value);
        void Send(CP_Code code, std::string value);
        virtual void SetSocket(Socket* socket);

        bool IsEnabled();
        void SetEnable(bool enabled);

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
        bool enabled;
};

#endif