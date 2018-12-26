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

#include "includes/Enums.h"

HardwareControl* hardwareControl;
SerialClient* client;
Program* program;

/*
void handleIncomingMessages()
{
    std::vector<String> message = client->ReadMessage();

    if (message.size() < 1)
    {
        return;
    }

    // PING
    else if (message[0].equals("0"))
    {
        client->SendMessage(M_PING);
    }

    // START PROGRAM
    else if (message[0].equals("1"))
    {
        if (message.size() < 2)
        {
            String response = "1";
            client->SendMessage(M_PROGRAM_START, &response, 1);
            return;
        }

        int program = message[1].toInt();
        String response = machine->SetProgram(program)
            ? "0"
            : "1";

        client->SendMessage(M_PROGRAM_START, &response, 1);
    }
}
*/

void setup()
{
    Serial.begin(9600);

    // Connect to the remote server.
    Serial.println("Connecting to the Wi-Fi network...");

    // client = new WifiClient("12connect", "192.168.200.73", Protocol::GetPort());
    client = new SerialClient();

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

    // Initialize the hardware control.
    hardwareControl = new HardwareControl(new CentipedeShield(), new Controls(), new Heater(), new Motor(), new Water());

    program = new Program(hardwareControl, client);

    program->AddAction(new MotorRotateAction(MD_LEFT, SPEED_LOW));
    program->AddAction(new DelayAction(5000L));
    program->AddAction(new MotorRotateAction(MD_RIGHT, SPEED_LOW));
    program->AddAction(new DelayAction(5000L));
    program->AddAction(new MotorRotateAction(MD_LEFT, SPEED_LOW));
    program->AddAction(new DelayAction(5000L));
    program->AddAction(new MotorRotateAction(MD_RIGHT, SPEED_LOW));
    program->AddAction(new DelayAction(5000L));

    Serial.println("Starting...");

    // Must set first action otherwise nothing will happen.
    program->SetNextAction();
}

void loop()
{
    program->Update();

    /*
    if (client->IsDataAvailable())
    {
        handleIncomingMessages();
    }
    */
}
