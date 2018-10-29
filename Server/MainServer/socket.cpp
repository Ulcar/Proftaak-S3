#include "socket.h"

Socket::Socket(int socketFd)
{
    ETA = 0;
    error = Error::None;
    this->socketFd = socketFd;
    Send("Welcome socket");
}

Socket::~Socket()
{
    close(socketFd);
}

void Socket::Send(std::string text)
{
    size_t nrBytesRec = send(socketFd, text.c_str(), text.length(), 0);
    if (nrBytesRec != text.length())
    {
        std::cout << "not everything is sent (" << nrBytesRec << "/" << text.length() << " bytes sent)\n";
    }
}

std::string Socket::Read()
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
        delete this;
        return "";
    }
    return buffer;
}

int Socket::Ping()
{
    return 0;
}