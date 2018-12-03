#include "controlpanel.h"
#include "enums.h"


ControlPanel::ControlPanel(std::string macAdress)
    : macAdress(macAdress)
{
    
}

ControlPanel::~ControlPanel()
{
    delete socket;
}

void ControlPanel::Send(Code code, int value)
{
    if(socket == nullptr)
    {
        return;
    }
    socket->NewSendMessage(Protocol::ToClient(code, value));
}

void ControlPanel::SetSocket(Socket* tempSocket)
{
    if(socket != nullptr)
    {
        delete tempSocket;
    }
    socket = tempSocket;
}

void ControlPanel::Beat()
{
    std::string message = socket->ReadLastMessage();
    if(message.empty())
    {
        return;
    }

    //handle message
}
