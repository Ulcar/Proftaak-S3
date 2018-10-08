#ifndef PROTOCOL_H
#define PROTOCOL_H

class Protocol
{
    public:
        static int GetPort()
        {
            return port;
        }
        static std::string ToClient(std::vector<std::string> message);
        static std::vector<std::string> FromClient(std::string);
        static std::string ToInterface(std::vector<std::string> message);
        static std::vector<std::string> FromInterface(std::string);

    private:
        static const int port = 2018; //set port here

};

#endif

