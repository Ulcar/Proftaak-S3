#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "harnass/ArduinoWrapper.h"
#include "mock/MTransport.h"

#include "MainClient.ino"

using ::testing::Return;
using ::testing::Test;
using ::testing::_;

void OnMessageReceived(std::vector<String> message)
{
    EXPECT_EQ(message[0], String(M_PING));
    EXPECT_EQ(message[1], String("0"));
}

class MainClientTest : public ::testing::Test
{
protected:
    MainClient* client;
    MTransport transport;

    MainClientTest()
    {
        client = new MainClient(&transport, OnMessageReceived);
    }
};

TEST_F(MainClientTest, TestSendCorrectlyEncodesTheMessage)
{
    EXPECT_CALL(transport, Send(String("&5;1#")));

    client->Send(M_PROGRAM_DONE, { "1" });
}

TEST_F(MainClientTest, TestReceiveCorrectlyDecodesTheMessage)
{
    EXPECT_CALL(transport, Read(_)).WillOnce(Return(String("#6;0&")));

    client->Update();
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
