#include "socket.h"

Socket::Socket(int socketFd)
{
    ETA = 0;
    waitingForClient = false;
    this->socketFd = socketFd;
}

Socket::~Socket()
{
    close(socketFd);
}

//Called in external thread
bool Socket::Read()
{
    const int BufferSize = 100;
    char buffer[BufferSize];
    int nrBytesSend = read(socketFd, buffer, BufferSize - 1);
    if (nrBytesSend > 0)
    {
        buffer[nrBytesSend] = '\0';
        std::string fu = "Received from " + this->getSocketFd();
        fu += " a new message: ";
        fu += buffer;
        DebugLogger::Record(fu, "socket");
    }
    else if(nrBytesSend == 0)
    {
        std::string fu = "Socket " + this->getSocketFd();
        fu += " is shutdown. Disconnected";
        DebugLogger::Record(fu, "socket");
        return false;
    }

    AddMessageIn(buffer);
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
        std::string fu = "Socket " + this->getSocketFd();
        fu += " has not send everything (" + nrBytesRec;
        fu += "/" + text.length();
        fu += ")";
        DebugLogger::Record(fu, "socket");
    }
}

void Socket::TrySend()
{
    if(!waitingForClient && bufferOut.size() != 0)
    {
        Send(GetMessageToSend());
        waitingForClient = true;
    }
}



//mutexes

void Socket::AddMessageIn(std::string message)
{
    std::unique_lock<std::mutex> lock (mtxBufferIn);
    bufferIn.push_back(message);
}

std::string Socket::ReadLastMessage()
{
    std::unique_lock<std::mutex> lock (mtxBufferIn);
    if(bufferIn.size() == 0)
    {
        return "";
    }
    std::string last = bufferIn.at(0);
    bufferIn.erase(bufferIn.begin());
    return last;
}


void Socket::NewSendMessage(std::string message)
{
    std::unique_lock<std::mutex> lock (mtxBufferIn);
    bufferOut.push_back(message);
}

std::string Socket::GetMessageToSend()
{
    std::unique_lock<std::mutex> lock (mtxBufferIn);
    if(bufferOut.size() == 0)
    {
        return "";
    }
    std::string last = bufferOut.at(0);
    bufferOut.erase(bufferOut.begin());
    return last;
}