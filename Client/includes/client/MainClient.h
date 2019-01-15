#ifndef ICLIENT_H
#define ICLIENT_H

#ifdef __AVR__
#include <ArduinoSTL.h>
#endif

#include "ITransport.h"
#include "../Enums.h"

#define SEPARATOR_CHARACTER     (';')

#define SEND_START_CHARACTER    ('&')
#define SEND_END_CHARACTER      ('#')

#define RECEIVE_START_CHARACTER ('#')
#define RECEIVE_END_CHARACTER   ('&')

typedef void (*OnMessageReceivedCallback)(std::vector<String>);

// Because Arduino has its own 'Client' class, we aren't able to use the name
// 'Client' for this class (even though it should).
class MainClient
{
public:
    MainClient(ITransport* transport, OnMessageReceivedCallback callback);

    bool ConnectToNetwork();
    bool ConnectToServer(MachineType type);

    void Send(MessageCode code, std::vector<String> parameters);
    void Update();
    void Reset();

    bool IsConnectedToNetwork();
    bool IsConnectedToServer();

protected:
    OnMessageReceivedCallback _callback;
    ITransport* _transport;
    bool _isConnectedToServer;

    MainClient(const MainClient& other);
    MainClient& operator=(const MainClient& other);

    String EncodeMessage(MessageCode code, std::vector<String> parameters);
    std::vector<String> DecodeMessage(String message);
};

#endif
