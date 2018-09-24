#ifndef CLIENT_H
#define CLIENT_H

class Client
{
    public:
        Client();
        ~Client();
        void Send();
        void Read();
        int Ping();

    private:
        int error;
};

#endif