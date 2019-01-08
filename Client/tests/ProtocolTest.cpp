#include <gtest/gtest.h>

#include "harnass/ArduinoWrapper.h"

#include "Protocol.ino"

TEST(ProtocolTest, TestToServerGeneratesCorrectMessage)
{
    String result = Protocol::ToServer(M_PROGRAM_DONE, { "1" });

    EXPECT_EQ(String("&5;1#"), result);
}

TEST(ProtocolTest, TestFromServerDecodesCorrectlyWithoutStartAndEndChars)
{
    String message = String("6;0");

    std::vector<String> expectedParameters = { String(M_PING), "0" };
    std::vector<String> parameters = Protocol::FromServer(message);

    EXPECT_EQ(expectedParameters, parameters);
}

TEST(ProtocolTest, TestFromServerDecodesCorrectlyWithStartAndEndChars)
{
    String message = String("#2;5;6&");

    std::vector<String> expectedParameters = { String(M_STOP_TAKE_WATER), "5", "6" };
    std::vector<String> parameters = Protocol::FromServer(message);

    EXPECT_EQ(expectedParameters, parameters);
}
