#ifndef MOCKCLIENT_H
#define MOCKCLIENT_H

#include <gmock/gmock.h>
#include <string>

#include "includes/client/IClient.h"
#include "includes/Enums.h"

class MockClient : public IClient
{
public:
    MOCK_METHOD1(ConnectToServer, bool(MachineType));

    MOCK_METHOD2(SendMessage, void(MessageCode, std::vector<String>));
    MOCK_METHOD0(GetMacAddress, String());
    MOCK_METHOD0(IsConnectedToServer, bool());
    MOCK_METHOD0(IsDataAvailable, bool());

    void InjectMessage(std::vector<String> message)
    {
        _injectedMessage = message;
    }

    std::vector<String> ReadMessage(bool shouldBlock = false)
    {
        return _injectedMessage;
    }

private:
    std::vector<String> _injectedMessage;
};

#endif
