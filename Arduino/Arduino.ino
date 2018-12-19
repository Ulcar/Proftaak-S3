#include "includes/hardware/HardwareControl.h"
#include "includes/hardware/CentipedeShield.h"
#include "includes/hardware/Controls.h"
#include "includes/hardware/Heater.h"
#include "includes/hardware/Motor.h"
#include "includes/hardware/Water.h"

#include "includes/client/SerialClient.h"
#include "includes/client/Protocol.h"

#include "includes/machine/Machine.h"
#include "includes/machine/Actions.h"

#include "includes/Enums.h"

HardwareControl* hardwareControl;
SerialClient* client;

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

    Machine machine(*hardwareControl, client);

    Vector<IAction*> actions;
    actions.push_back(new FillWaterAction(3));
    actions.push_back(new HeatAction(2));

    machine.NewProgram(0, actions);
    machine.StartProgram(0);
}

void loop()
{
}
