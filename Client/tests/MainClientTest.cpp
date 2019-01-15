#include <gtest/gtest.h>

#include "harnass/ArduinoWrapper.h"
#include "mock/MTransport.h"

#include "MainClient.ino"

class MainClientTest : public ::testing::Test
{
protected:
    MainClient* client;
    MTransport* transport;

    MainClientTest()
    {
        client = new MainClient(transport, NULL);
    }
};

TEST_F(MainClientTest, TestSendCorrectlyEncodesTheMessage)
{
    EXPECT_CALL(transport, Send("&5;1#"));

    client->Send(M_PROGRAM_DONE, { "1" });
    /*String result = Protocol::ToServer(M_PROGRAM_DONE, { "1" });

    EXPECT_EQ(String("&5;1#"), result);*/
}

/*TEST_F(ProtocolTest, TestFromServerDecodesCorrectlyWithoutStartAndEndChars)
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
}*/
