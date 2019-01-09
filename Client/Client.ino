#include "includes/hardware/HardwareControl.h"
#include "includes/hardware/CentipedeShield.h"
#include "includes/hardware/StatusIndicator.h"
#include "includes/hardware/Controls.h"
#include "includes/hardware/Heater.h"
#include "includes/hardware/Motor.h"
#include "includes/hardware/Water.h"

#include "includes/client/WifiClient.h"
#include "includes/client/Protocol.h"

#include "includes/program/Actions.h"
#include "includes/program/Program.h"
#include "includes/program/Programs.h"

#include "includes/Enums.h"

#define WATER_TANK_SIZE (20)
#define HEATER_WATT     (500)

HardwareControl* hardwareControl;
WifiClient* client;
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
    {
        // If we don't have two parameters, we know that the command is invalid.
        if (message.size() < 2)
        {
            client->SendMessage(M_PROGRAM_START, { "1" });

            return;
        }

        int program = message[1].toInt();

        // If the program doesn't exist we send a "1" back, otherwise we start
        // the program and send a "0" back.
        client->SendMessage(M_PROGRAM_START, { programs->Start(program) ? "0" : "1" });
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
        Serial.println("Unrecognized command.");
        break;
    }
}

void onProgramDone()
{
    StatusIndicator* statusIndicator = hardwareControl->GetStatusIndicator();
    statusIndicator->SetStatus(S_DONE);

    client->SendMessage(M_PROGRAM_DONE, { "0" });
}

void setup()
{
    Serial.begin(9600);

    // Initialize the hardware control and program manager.
    StatusIndicator* statusIndicator = new StatusIndicator();

    hardwareControl = new HardwareControl(
        new CentipedeShield(),
        statusIndicator,
        new Controls(),
        new Heater(),
        new Motor(),
        new Water()
    );

    statusIndicator->SetStatus(S_DECOUPLED);

    // Connect to the remote server.
    Serial.println("Connecting to the Wi-Fi network...");

    client = new WifiClient("TP-LINK_Proftaak", "wasserete", "192.168.137.208", Protocol::GetPort());
    client->SetOnMessageReceived(onMessageReceived);

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

    statusIndicator->SetStatus(S_DONE);

    programs = new Programs(hardwareControl, client);
    programs->SetOnProgramDone(onProgramDone);

    Serial.println("Loading programs...");

    // Load program A.
    programs->Add(0, {
        // Prewash
        new RequestWaterAction(WATER_TANK_SIZE / 2),
        new FillWaterAction(WL_50),
        new HeatAction(TEMP_OFF),
        new SoapAction(STATE_ON, 1),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_OFF),
        new DrainWaterAction(),
        new SoapAction(STATE_OFF, 1),

        // Main wash (1)
        new RequestWaterAction(WATER_TANK_SIZE / 2),
        new FillWaterAction(WL_50),
        new RequestPowerAction(HEATER_WATT),
        new HeatAction(TEMP_MEDIUM),
        new SoapAction(STATE_ON, 2),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_OFF),
        new DrainWaterAction(),
        new SoapAction(STATE_OFF, 2),

        // Main wash (2)
        new RequestWaterAction(WATER_TANK_SIZE / 2),
        new FillWaterAction(WL_50),
        new HeatAction(TEMP_OFF),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_OFF),
        new DrainWaterAction(),

        // Centrifugation
        new MotorRotateAction(MD_LEFT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_RIGHT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_LEFT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_RIGHT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_RIGHT, SPEED_OFF),

        // Beep!
        new BuzzerAction(STATE_ON),
        new DelayAction(1000L),
        new BuzzerAction(STATE_OFF),
    });

    // Load program B.
    programs->Add(1, {
        // Prewash
        new RequestWaterAction(WATER_TANK_SIZE / 2),
        new FillWaterAction(WL_50),
        new RequestPowerAction(HEATER_WATT),
        new HeatAction(TEMP_MEDIUM),
        new SoapAction(STATE_ON, 1),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_OFF),
        new DrainWaterAction(),
        new SoapAction(STATE_OFF, 1),

        // Main wash (1)
        new RequestWaterAction(WATER_TANK_SIZE / 2),
        new FillWaterAction(WL_50),
        new RequestPowerAction(HEATER_WATT),
        new HeatAction(TEMP_MEDIUM),
        new SoapAction(STATE_ON, 2),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_OFF),
        new DrainWaterAction(),
        new SoapAction(STATE_OFF, 2),

        // Main wash (2)
        new RequestWaterAction(WATER_TANK_SIZE / 2),
        new FillWaterAction(WL_50),
        new HeatAction(TEMP_OFF),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_OFF),
        new DrainWaterAction(),

        // Centrifugation
        new MotorRotateAction(MD_LEFT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_RIGHT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_LEFT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_RIGHT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_RIGHT, SPEED_OFF),

        // Beep!
        new BuzzerAction(STATE_ON),
        new DelayAction(1000L),
        new BuzzerAction(STATE_OFF),
    });

    // Load program C.
    programs->Add(0, {
        // Prewash
        new RequestWaterAction(WATER_TANK_SIZE / 2),
        new FillWaterAction(WL_50),
        new RequestPowerAction(HEATER_WATT),
        new HeatAction(TEMP_MEDIUM),
        new SoapAction(STATE_ON, 1),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_OFF),
        new DrainWaterAction(),
        new SoapAction(STATE_OFF, 1),

        // Main wash (1)
        new RequestWaterAction(WATER_TANK_SIZE),
        new FillWaterAction(WL_FULL),
        new RequestPowerAction(HEATER_WATT),
        new HeatAction(TEMP_HOT),
        new SoapAction(STATE_ON, 2),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_OFF),
        new DrainWaterAction(),
        new SoapAction(STATE_OFF, 2),

        // Main wash (2)
        new RequestWaterAction(WATER_TANK_SIZE / 2),
        new FillWaterAction(WL_50),
        new HeatAction(TEMP_OFF),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_LEFT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_LOW),
        new DelayAction(10 * 1000L),
        new MotorRotateAction(MD_RIGHT, SPEED_OFF),
        new DrainWaterAction(),

        // Centrifugation
        new MotorRotateAction(MD_LEFT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_RIGHT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_LEFT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_RIGHT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_LEFT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_RIGHT, SPEED_HIGH),
        new DelayAction(5000L),
        new MotorRotateAction(MD_RIGHT, SPEED_OFF),

        // Beep!
        new BuzzerAction(STATE_ON),
        new DelayAction(1000L),
        new BuzzerAction(STATE_OFF),
    });

    Serial.println("Done loading programs.");
}

void loop()
{
    programs->Update();
    client->Update();

    StatusIndicator* statusIndicator = hardwareControl->GetStatusIndicator();
    statusIndicator->Update();
}
