#ifndef SERIALCLIENT_H
#define SERIALCLIENT_H

#include <ArduinoSTL.h>

#include "ITransport.h"

class SerialTransport : public ITransport
{
public:
    SerialTransport();
    ~SerialTransport();

    bool ConnectToNetwork();
    bool ConnectToServer();

    bool IsConnectedToNetwork();

    void Send(String data);
    String Read(bool shouldBlock = false);

    String GetMacAddress();

private:
    String _message;

    SerialTransport(const SerialTransport& other);
    SerialTransport& operator=(const SerialTransport& other);
};

#endif
