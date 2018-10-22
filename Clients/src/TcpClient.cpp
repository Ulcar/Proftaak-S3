#include "TcpClient.h"
#include "protocol.h"

TcpClient::TcpClient()
    : _connected(false)
{
}

TcpClient::~TcpClient()
{
    if (!_connected)
    {
        Disconnect();
    }
}

void TcpClient::Connect(const std::string& host, int port)
{
    if (_connected)
    {
        throw std::logic_error("TcpClient is already connected.");
    }

    if ((_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
    {
        throw std::runtime_error("Unable to create a socket.");
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (inet_pton(AF_INET, host.c_str(), &addr.sin_addr) != 1)
    {
        throw std::runtime_error("Could not convert IP address to network address structure.");
    }

    if (connect(_socket, (struct sockaddr*)&addr, sizeof(addr)) == -1)
    {
        throw std::runtime_error("Unable to create a connection.");
    }

    _connected = true;
}

void TcpClient::Disconnect()
{
    if (!_connected)
    {
        throw std::logic_error("There is no connection to close.");
    }

    if (close(_socket) != 0)
    {
        throw std::runtime_error("Failed to close the socket.");
    }

    _connected = false;
}

void TcpClient::Send(const std::string data)
{
    if (!_connected)
    {
        throw std::logic_error("There is no connection.");
    }

    std::string dataToSend = Protocol::ToServer(data);
    if (send(_socket, dataToSend.c_str(), dataToSend.length(), 0) < 0)
    {
        throw std::runtime_error("Something went wrong while sending a message.");
    }
}

void TcpClient::Send(std::vector<std::string> data)
{
    if (!_connected)
    {
        throw std::logic_error("There is no connection.");
    }
    std::string dataToSend = Protocol::ToServer(data);
    if (send(_socket, dataToSend.c_str(), dataToSend.length(), 0) < 0)
    {
        throw std::runtime_error("Something went wrong while sending a message.");
    }
}

std::string TcpClient::Read()
{
    if (!_connected)
    {
        throw std::logic_error("There is no connection.");
    }

    char buffer[READ_BUFFER_SIZE] = { 0 };

    if (recv(_socket, buffer, READ_BUFFER_SIZE, 0) > 0)
    {
        return std::string(buffer);
    }

    throw std::runtime_error("Something went wrong while reading a message.");
}
