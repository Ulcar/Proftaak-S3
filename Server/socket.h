#ifndef SOCKET_H
#define SOCKET_H

class Socket
{
    public:
        Socket();
        ~Socket();
        void Send();
        int Ping();

    private:
        int error;
        int ETA;
};

#endif