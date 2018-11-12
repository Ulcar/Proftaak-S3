#include "socket.h"

Socket::Socket(int socketFd)
{
    ETA = 0;
    error = Error::None;
    waitingForClient = false;
    this->socketFd = socketFd;
}

Socket::~Socket()
{
    close(socketFd);
}

void Socket::QueSend(std::string text)
{
    bufferOut.push_back(text);
}

bool Socket::Read()
{
    const int BufferSize = 100;
    char buffer[BufferSize];
    int nrBytesSend = read(socketFd, buffer, BufferSize - 1);
    if (nrBytesSend > 0)
    {
        buffer[nrBytesSend] = '\0';
        std::cout << "received " << nrBytesSend << " bytes: " << buffer << std::endl;
    }
    else if(nrBytesSend == 0)
    {
        std::cout << "Socket is shutdown. Disconnected\n";
        return false;
    }

    bufferIn.push_back(buffer);
    return true;
}

int Socket::Ping()
{
    return 0;
}

void Socket::Send(std::string text)
{
    size_t nrBytesRec = send(socketFd, text.c_str(), text.length(), 0);
    if (nrBytesRec != text.length())
    {
        std::cout << "Not everything is sent (" << nrBytesRec << "/" << text.length() << " bytes sent)\n";
    }
}

bool Socket::Beat()
{
    if(!waitingForClient && bufferOut.size() != 0)
    {
        QueSend(bufferOut.at(0));
        waitingForClient = true;
    }
    
    if(bufferIn.size() != 0)
    {
        return true;
    }
    return false;
}