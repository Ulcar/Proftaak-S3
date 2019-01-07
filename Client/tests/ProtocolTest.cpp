#include <gtest/gtest.h>

#include "harnass/ArduinoWrapper.h"
#include "includes/client/Protocol.h"

#include "Protocol.ino"

TEST(ProtocolTest, ToServer)
{
    String result = Protocol::ToServer(M_PROGRAM_DONE, { "1" });

    EXPECT_EQ("&1:1#", result);
}
