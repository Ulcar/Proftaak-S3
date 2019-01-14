#include "includes/hardware/HardwareControl.h"
#include "includes/hardware/CentipedeShield.h"
#include "includes/hardware/StatusIndicator.h"
#include "includes/hardware/Controls.h"
#include "includes/hardware/Heater.h"
#include "includes/hardware/Motor.h"
#include "includes/hardware/Water.h"

#include "includes/client/WifiTransport.h"
#include "includes/client/MainClient.h"

#include "includes/program/Actions.h"
#include "includes/program/Program.h"
#include "includes/program/Programs.h"

#include "includes/Enums.h"

#define WATER_TANK_SIZE (20)
#define HEATER_WATT     (500)

// Because we need to be able to access these variables in both the 'setup' and
// 'loop' methods we made these variables global. While we could have created a
// 'Arduino' class which manage these variables, we would still need one global
// variable.
HardwareControl* hardwareControl;
MainClient* client;
Programs* programs;

void onMessageReceived(std::vector<String> message)
{
    bool isValid = true;

    // Verify that the first part of the message (the message code) is an
    // integer.
    for (int i = 0; i < message[0].length(); ++i)
    {
        if (!isDigit(message[0][i]))
        {
            isValid = false;
        }
    }

    if (!isValid)
    {
        Serial.println("Invalid message code received (" + message[0] + ")");

        return;
    }

    int command = message[0].toInt();

    switch (command)
    {
    case M_PING:
        client->Send(M_PING, { "0" });
        break;

    case M_PROGRAM_START:
    {
        // If we don't have two parameters, we know that the command is invalid.
        if (message.size() < 2)
        {
            client->Send(M_PROGRAM_START, { "1" });

            return;
        }

        int program = message[1].toInt();

        if (programs->Start(program))
        {
            Serial.println("Starting program #" + String(program));

            client->Send(M_PROGRAM_START, { "0" });
        }
        else
        {
            Serial.println("Unknown program (" + String(program) + ")");

            client->Send(M_PROGRAM_START, { "1" });
        }
        break;
    }

    case M_MAY_TAKE_WATER:
        // If we don't have two parameters, we know that the command is invalid.
        if (message.size() < 2)
        {
            return;
        }

        if (message[1] == "0")
        {
            programs->AllowTakeWater();
        }
        break;

    case M_MAY_HEAT_UP:
        // If we don't have two parameters, we know that the command is invalid.
        if (message.size() < 2)
        {
            return;
        }

        if (message[1] == "0")
        {
            programs->AllowHeatUp();
        }
        break;

    default:
        Serial.println("Unrecognized command (" + message[0] + ").");
        break;
    }
}

void onProgramDone()
{
    StatusIndicator* statusIndicator = hardwareControl->GetStatusIndicator();
    statusIndicator->SetStatus(S_DONE);

    client->Send(M_PROGRAM_DONE, { "0" });
}

void setup()
{
    Serial.begin(9600);

    // Initialize the hardware control and program manager.
    //  We pass these objects as pointers to the HardwareControl because we use
    //  interfaces (ICentipedeShield, etc.). If we don't do this we get an error:
    //  'Cannot declare parameter to be of abstract type'. We also delegate the
    //  removal of these pointers to the HardwareControl.
    hardwareControl = new HardwareControl(
        new CentipedeShield(),
        new StatusIndicator(),
        new Controls(),
        new Heater(),
        new Motor(),
        new Water()
    );

    // Connect to the remote server.
    Serial.println("Connecting to the Wi-Fi network...");

    client = new MainClient(new WifiTransport("TP-LINK_Proftaak", "wasserete", "192.168.137.102", 57863), onMessageReceived);

    Serial.println("Connected to the Wi-Fi network.");

    while (!client->IsConnectedToServer())
    {
        Serial.println("Connecting to the server...");

        if (!client->ConnectToServer(MT_WASMACHINE))
        {
            Serial.println("Could not connect to the server.");

            delay(5000);

            Serial.println("Retrying connection...");
        }
    }

    Serial.println("Connected to the server.");

    StatusIndicator* statusIndicator = hardwareControl->GetStatusIndicator();
    statusIndicator->SetStatus(S_DONE);

    // Initialize the program manager.
    programs = new Programs(hardwareControl, client, onProgramDone);

    Serial.println("Loading programs...");

    String json = "{\"program\":0,\"actions\":[{\"action\":7,\"args\":{\"direction\":0,\"speed\":1}},{\"action\":8,\"args\":{\"ms\":5000}},{\"action\":7,\"args\":{\"direction\":0,\"speed\":1}},{\"action\":8,\"args\":{\"ms\":5000}}]}";

    programs->Add(json);

    Serial.println("Done loading programs.");
}

void loop()
{
    programs->Update();
    client->Update();

    StatusIndicator* statusIndicator = hardwareControl->GetStatusIndicator();
    statusIndicator->Update();
}
