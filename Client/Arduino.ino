#include <ArduinoSTL.h>

#include "includes/hardware/HardwareControl.h"
#include "includes/hardware/CentipedeShield.h"
#include "includes/hardware/Controls.h"
#include "includes/hardware/Heater.h"
#include "includes/hardware/Motor.h"
#include "includes/hardware/Water.h"

#include "includes/client/SerialClient.h"
#include "includes/client/Protocol.h"

#include "includes/program/Actions.h"
#include "includes/program/Program.h"
#include "includes/program/Programs.h"

#include "includes/Enums.h"

HardwareControl* hardwareControl;
SerialClient* client;
Programs* programs;

void onMessageReceived(std::vector<String> message)
{
    int command = message[0].toInt();

    switch (command)
    {
    case 0: // PING
        client->SendMessage(M_PING);
        break;

    case 7: // START_PROGRAM
        if (message.size() < 2)
        {
            String response = "1";
            client->SendMessage(M_PROGRAM_START, &response, 1);
            return;
        }

        int program = message[1].toInt();
        String response = programs->Start(program)
            ? "0"
            : "1";

        Serial.println("Starting program: " + String(program));
        client->SendMessage(M_PROGRAM_START, &response, 1);
        break;

    default:
        Serial.println("Unrecognized command.");
        break;
    }
}

void setup()
{
    Serial.begin(9600);

    // Connect to the remote server.
    Serial.println("Connecting to the Wi-Fi network...");

    // client = new WifiClient("12connect", "192.168.200.73", Protocol::GetPort());
    client = new SerialClient();
    client->SetOnMessageReceived(onMessageReceived);

    Serial.println("Connected to the Wi-Fi network.");

    while (!client->IsConnectedToServer())
    {
        Serial.println("Connecting to the server...");

        if (!client->ConnectToServer(MT_WASMACHINE))
        {
            Serial.println("Could not connect to the server.");
        }

        if (!client->IsConnectedToServer())
        {
            delay(1000);

            Serial.println("Retrying connection...");
        }
    }

    Serial.println("Connected to the server.");

    // Initialize the hardware control and program manager.
    hardwareControl = new HardwareControl(new CentipedeShield(), new Controls(), new Heater(), new Motor(), new Water());
    programs = new Programs(hardwareControl, client);

    Serial.println("Loading programs...");

    // Load program A
    programs->Add(0, {
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(5000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(5000L),
    });

    // Load program B
    programs->Add(1, {
        new MotorRotateAction(MD_LEFT, SPEED_MEDIUM),
        new DelayAction(5000L),
        new MotorRotateAction(MD_RIGHT, SPEED_MEDIUM),
        new DelayAction(5000L),
    });

    // Load program C
    programs->Add(2, {
        new MotorRotateAction(MD_LEFT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_RIGHT, SPEED_HIGH),
        new DelayAction(5000L),
    });

    Serial.println("Done!");
}

void loop()
{
    programs->Update();
    client->Update();
}
