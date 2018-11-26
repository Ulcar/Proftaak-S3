#ifndef ISOCKETIO_H
#define ISOCKETIO_H

#include <string>

class iSocketIO
{
public:
    virtual ~iSocketIO() {};
/*
        Socket(int socketFd);
        ~Socket();
        int Ping();
        void TrySend();
        bool Read();
        void NewSendMessage(std::string text);
        std::string ReadLastMessage();

        int getSocketFd()
        {
            return socketFd;
        }
    //virtual void TurnLeft() = 0;
    */
};

#endif
