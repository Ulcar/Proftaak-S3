#ifndef ICLIENT_H
#define ICLIENT_H

#define RECEIVE_CHARACTER_START ('#')
#define RECEIVE_CHARACTER_END   ('&')

#define SEND_CHARACTER_START    ('&')
#define SEND_CHARACTER_END      ('#')

class IClient
{
public:
    virtual bool ConnectToServer() = 0;

    virtual void SendMessage(String data) = 0;
    virtual String ReadMessage(bool shouldBlock = true) = 0;

    virtual String GetMacAddress() = 0;
    virtual bool IsConnected() = 0;
};

#endif
