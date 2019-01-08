#include "includes/client/Protocol.h"

String Protocol::ToServer(MessageCode code, std::vector<String> parameters)
{
    String result = SEND_START_CHARACTER + String(code);

    for (int i = 0; i < parameters.size(); ++i)
    {
        if (parameters[i].length() > 0)
        {
            result += SEPARATOR_CHARACTER + parameters[i];
        }
    }

    result += SEND_END_CHARACTER;

    return result;
}

std::vector<String> Protocol::FromServer(String message)
{
    // Make sure that there are no start and end characters.
    if (message[0] == RECEIVE_START_CHARACTER)
    {
        message = message.substring(1, message.length());
    }

    if (message[message.length() - 1] == RECEIVE_END_CHARACTER)
    {
        message = message.substring(0, message.length() - 1);
    }

    std::vector<String> command;
    size_t prevIndex = 0;

    while (true)
    {
        size_t index = message.indexOf(SEPARATOR_CHARACTER, prevIndex);

        // Test to see if there is only one part remaining. When there's only one
        // part remaining, the 'index' will be the maximum value of an integer.
        if (index > message.length())
        {
            command.push_back(message.substring(prevIndex, message.length()));

            break;
        }

        // Extract a part of the message.
        command.push_back(message.substring(prevIndex, index));

        prevIndex = index + 1;
    }

    return command;
}
