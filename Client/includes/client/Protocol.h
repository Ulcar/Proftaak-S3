#ifndef PROTOCOL_H
#define PROTOCOL_H

#ifdef __AVR__
#include <ArduinoSTL.h>
#endif

#include "../Enums.h"

#define SEPARATOR_CHARACTER     (';')

#define SEND_START_CHARACTER    ('&')
#define SEND_END_CHARACTER      ('#')

#define RECEIVE_START_CHARACTER ('#')
#define RECEIVE_END_CHARACTER   ('&')

class Protocol
{
public:
    static String ToServer(MessageCode code, std::vector<String> parameters);
    static std::vector<String> FromServer(String message);
};

#endif
