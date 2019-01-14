#include "includes/hardware/HardwareControl.h"
#include "includes/hardware/CentipedeShield.h"
#include "includes/hardware/StatusIndicator.h"
#include "includes/hardware/Controls.h"
#include "includes/hardware/Heater.h"
#include "includes/hardware/Motor.h"
#include "includes/hardware/Water.h"

#include "includes/client/SerialClient.h"
#include "includes/client/WifiClient.h"
#include "includes/client/Protocol.h"

#include "includes/program/Actions.h"
#include "includes/program/Program.h"
#include "includes/program/Programs.h"

#include "includes/Enums.h"

HardwareControl* hardwareControl;
IClient* client;
Programs* programs;

void onMessageReceived(std::vector<String> message)
{
    int command = message[0].toInt();

    switch (command)
    {
    case M_PING:
        client->SendMessage(M_PING, { "0" });
        break;

    case M_PROGRAM_START:
        // If we don't have two parameters, we know that the command is invalid.
        if (message.size() < 2)
        {
            client->SendMessage(M_PROGRAM_START, { "1" });

            return;
        }

        int program = message[1].toInt();

        Serial.println("Starting program: " + String(program));

        // If the program doesn't exist we send a "1" back, otherwise we start
        // the program and send a "0" back.
        client->SendMessage(M_PROGRAM_START, { programs->Start(program) ? "0" : "1" });
        break;

    default:
        Serial.println("Unrecognized command.");
        break;
    }
}

void onProgramDone()
{
    Serial.println("Program done!");

    client->SendMessage(M_PROGRAM_DONE, { "0" });
}

void setup()
{
    Serial.begin(9600);

    Serial.println("helloworld");

    // Initialize the hardware control and program manager.
    hardwareControl = new HardwareControl(
        new CentipedeShield(),
        new StatusIndicator(),
        new Controls(),
        new Heater(),
        new Motor(),
        new Water()
    );

    programs = new Programs(hardwareControl, client);
    programs->SetOnProgramDone(onProgramDone);

    Serial.println("Loading programs...");

    String json = "{\"program\":0,\"actions\":[{\"action\":7,\"args\":{\"direction\":0,\"speed\":1}},{\"action\":8,\"args\":{\"ms\":5000}},{\"action\":7,\"args\":{\"direction\":0,\"speed\":1}},{\"action\":8,\"args\":{\"ms\":5000}}]}";

    programs->Add(json);
    programs->Start(0);

    Serial.println("Done!");

    Serial.println("Done loading programs.");

    analogWrite(46, HIGH);

    // Connect to the remote server.
    Serial.println("Connecting to the Wi-Fi network...");

    //client = new WifiClient("12connect", "192.168.200.40", Protocol::GetPort());
    client = new SerialClient();
    client->SetOnMessageReceived(onMessageReceived);

    Serial.println("Connected to the Wi-Fi network.");

    while (!client->IsConnectedToServer())
    {
        Serial.println("Connecting to the server...");

        if (!client->ConnectToServer(MT_WASMACHINE))
        {
            Serial.println("Could not connect to the server.");

            delay(1000);

            Serial.println("Retrying connection...");
        }
    }

    Serial.println("Connected to the server.");
}

void loop()
{
    programs->Update();
    client->Update();
}
