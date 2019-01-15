#ifndef MTRANSPORT_H
#define MTRANSPORT_H

#include <gmock/gmock.h>

#include "includes/client/ITransport.h"

class MTransport : public ITransport
{
public:
    MOCK_METHOD0(ConnectToNetwork, bool());
    MOCK_METHOD0(ConnectToServer, bool());

    MOCK_METHOD1(Send, void(String));
    MOCK_METHOD1(Read, String(bool));

    MOCK_METHOD0(IsConnectedToNetwork, bool());

    MOCK_METHOD0(GetMacAddress, String());
};

#endif
