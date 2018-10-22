#ifndef __TCP_CLIENT_H__
#define __TCP_CLIENT_H__

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <stdexcept>
#include <string>
#include <unistd.h>
#include <vector>

#define READ_BUFFER_SIZE 4096

class TcpClient
{
public:
    TcpClient();
    ~TcpClient();

    void Connect(const std::string& host, int port);
    void Disconnect();

    void Send(const std::string data);
    std::string Read();

    bool IsConnected();

private:
    bool _connected;
    int _socket;
};

#endif
