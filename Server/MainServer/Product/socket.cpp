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
        Logger::Record(false, "Received from " + std::to_string(this->getSocketFd()) + " a new message: " + buffer, "socket");
    }
    else if(nrBytesSend == 0)
    {
        Logger::Record(false, "Socket " + std::to_string(this->getSocketFd()) + " is shutdown. Disconnected", "socket");
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
        Logger::Record(false, "Socket " + std::to_string(this->getSocketFd()) + " has not send everything (" + std::to_string(nrBytesRec) + "/" + std::to_string(text.length()) + ")", "socket");
    }
    Logger::Record(false, "Socket: " + std::to_string(this->getSocketFd()) + " Send message: " + text, "socket");
}

void Socket::TrySend()
{
    if(!waitingForClient && bufferOut.size() != 0)
    {
        Send(GetMessageToSend());
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
    std::unique_lock<std::mutex> lock (mtxBufferOut);
    bufferOut.push_back(message);
    Logger::Record(false, "Socket: " + std::to_string(this->getSocketFd()) + " Added message to buffer: " + message, "Socket");
}

std::string Socket::GetMessageToSend()
{
    std::unique_lock<std::mutex> lock (mtxBufferOut);
    if(bufferOut.size() == 0)
    {
        return "";
    }
    std::string last = bufferOut.at(0);
    bufferOut.erase(bufferOut.begin());
    return last;
}