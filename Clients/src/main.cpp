#include <iostream>

#include "TcpClient.h"

int main()
{
    TcpClient* client = new TcpClient();
    client->Connect("127.0.0.1", 1337);

    while (true) {
        std::string data = client->Read();

        if (data.length() > 0) {
            std::cout << data << std::endl;

            client->Send("&ACK#");
        }
    }

    delete client;

    return 0;
}
