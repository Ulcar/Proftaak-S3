/*#include <SPI.h>
#include <SD.h>*/

#include "includes/hardware/HardwareControl.h"
#include "includes/hardware/CentipedeShield.h"
#include "includes/hardware/StatusIndicator.h"
#include "includes/hardware/Controls.h"
#include "includes/hardware/Heater.h"
#include "includes/hardware/Motor.h"
#include "includes/hardware/Water.h"

#include "includes/client/WifiTransport.h"
#include "includes/client/MainClient.h"

#include "includes/program/Program.h"
#include "includes/program/Programs.h"

#include "includes/Enums.h"

#define CONNECTION_LOST_TIMEOUT (30)
#define RETRY_TIMEOUT           (5)

#define SD_SHIELD               (4)

// Because we need to be able to access these variables in both the 'setup' and
// 'loop' methods we made these variables global. While we could have created a
// 'Arduino' class which manage these variables, we would still need one global
// variable.
HardwareControl* hardwareControl;
MainClient* client;
Programs* programs;

unsigned long lastPing = 0;

void Connect()
{
    client->Reset();

    while (!client->IsConnectedToNetwork())
    {
        Serial.println("Connecting to the Wi-Fi network...");

        if (!client->ConnectToNetwork())
        {
            Serial.println("Could not connect to the Wi-Fi network.");

            delay(RETRY_TIMEOUT * 1000L);

            Serial.println("Retrying connection...");
        }
    }

    Serial.println("Connected to the Wi-Fi network.");

    while (!client->IsConnectedToServer())
    {
        Serial.println("Connecting to the server...");

        if (!client->ConnectToServer(MT_WASMACHINE))
        {
            Serial.println("Could not connect to the server.");

            delay(RETRY_TIMEOUT * 1000L);

            Serial.println("Retrying connection...");
        }
    }

    Serial.println("Connected to the server.");

    lastPing = millis();
}

bool IsNumber(String message)
{
    for (int i = 0; i < message.length(); ++i)
    {
        if (!isDigit(message[i]))
        {
            return false;
        }
    }

    return true;
}

void OnMessageReceived(std::vector<String> message)
{
    if (!IsNumber(message[0]))
    {
        Serial.println("Invalid message code received (" + message[0] + ")");

        return;
    }

    int command = message[0].toInt();

    switch (command)
    {
    case M_PING:
        lastPing = millis();

        client->Send(M_PING, { "0" });
        break;

    case M_PROGRAM_START:
    {
        // Test if the parameters are valid.
        if (message.size() < 2 || !IsNumber(message[1]))
        {
            client->Send(M_PROGRAM_START, { "1" });

            return;
        }

        int program = message[1].toInt();

        if (programs->Start(program))
        {
            Serial.println("Starting program #" + message[1]);

            client->Send(M_PROGRAM_START, { "0" });
        }
        else
        {
            Serial.println("Unknown program (" + message[1] + ")");

            client->Send(M_PROGRAM_START, { "1" });
        }
        break;
    }

    case M_MAY_TAKE_WATER:
        // Test if the parameters are valid.
        if (message.size() < 2 || !IsNumber(message[1]))
        {
            return;
        }

        if (message[1] == "0")
        {
            programs->AllowTakeWater();
        }
        break;

    case M_MAY_HEAT_UP:
        // Test if the parameters are valid.
        if (message.size() < 2 || !IsNumber(message[1]))
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

void OnProgramDone()
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
    client = new MainClient(new WifiTransport("TP-LINK_Proftaak", "wasserete", "192.168.137.102", 57863), OnMessageReceived);

    Connect();

    StatusIndicator* statusIndicator = hardwareControl->GetStatusIndicator();
    statusIndicator->SetStatus(S_DONE);

    // Initialize the program manager.
    programs = new Programs(hardwareControl, client, OnProgramDone);

    /*Serial.println("Initializing SD card...");

    if (!SD.begin(SD_SHIELD))
    {
        Serial.println("Initialization failed.");
    }

    File root = SD.open("/");*/

    Serial.println("Loading programs...");

    //programs->Load(root);
    AddPrograms(programs);

    Serial.println("Done loading programs.");
}

void loop()
{
    StatusIndicator* statusIndicator = hardwareControl->GetStatusIndicator();

    if (millis() - lastPing > CONNECTION_LOST_TIMEOUT * 1000L)
    {
        Serial.println("Lost connection to server, reconnecting...");

        programs->Reset();
        hardwareControl->Initialize();

        statusIndicator->SetStatus(S_DECOUPLED);

        Connect();

        statusIndicator->SetStatus(S_DONE);
    }

    programs->Update();
    client->Update();

    statusIndicator->Update();
}
