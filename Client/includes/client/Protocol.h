#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <ArduinoSTL.h>

#include "../Enums.h"

#define SEPARATOR_CHARACTER     (';')

#define SEND_START_CHARACTER    ('&')
#define SEND_END_CHARACTER      ('#')

#define RECEIVE_START_CHARACTER ('#')
#define RECEIVE_END_CHARACTER   ('&')

class Protocol
{
public:
    static int GetPort()
    {
        return port;
    }

    static String ToServer(Message code, std::vector<String> parameters);
    static std::vector<String> FromServer(String);

private:
    static const int port = 2018;
};

#endif
