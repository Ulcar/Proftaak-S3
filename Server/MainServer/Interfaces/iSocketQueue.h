#ifndef ISOCKETQUEUE_H
#define ISOCKETQUEUE_H

#include <string>

class iSocketQueue
{
public:
    virtual ~iSocketQueue() {};

    virtual void NewSendMessage(std::string text) = 0;
    virtual std::string ReadLastMessage() = 0;
    virtual int getSocketFd() = 0;

    //virtual void TurnLeft() = 0;
};

#endif
