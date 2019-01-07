#ifndef MOCKCLIENT_H
#define MOCKCLIENT_H

#include <gmock/gmock.h>
#include <string>

#include "includes/client/IClient.h"

class MockClient : public IClient
{
public:
    MOCK_METHOD0(ConnectToServer, bool());

    MOCK_METHOD1(SendMessage, void(String));
    MOCK_METHOD0(GetMacAddress, std::string());
    MOCK_METHOD0(IsConnected, bool());

    void InjectMessage(std::string message)
    {
        _injectedMessage = message;
    }

    std::string ReadMessage(bool shouldBlock = true)
    {
        return _injectedMessage;
    }

private:
    String _injectedMessage;
};

#endif
