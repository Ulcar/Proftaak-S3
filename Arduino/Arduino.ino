#include "includes/hardware/HardwareControl.h"
#include "includes/hardware/Controls.h"
#include "includes/hardware/Heater.h"
#include "includes/hardware/Motor.h"
#include "includes/hardware/Water.h"

// #include "includes/client/WifiClient.h"
#include "includes/client/SerialClient.h"

#include "includes/machine/Machine.h"
#include "includes/machine/Actions.h"

#include "includes/Enums.h"

HardwareControl* hardwareControl;
/* WifiClient* client; */
SerialClient* client;

void setup()
{
    Serial.begin(9600);

    // Connect to the remote server.
    Serial.println("Connecting to the Wi-Fi network...");

    // client = new WifiClient("12connect", "192.168.200.73", 1337);
    client = new SerialClient();

    Serial.println("Connected to the Wi-Fi network.");
    Serial.println("Connecting to the server...");

    if (!client->ConnectToServer())
    {
        Serial.println("Could not connect to the server. Aborting.");

        while (true);
    }

    // Send the 'connect' message to the server.
    client->SendMessage("CONNECT;" + String(MT_WASMACHINE) + ";" + String(client->GetMacAddress()));

    // Wait for the 'accept' response of the previous message.
    if (client->ReadMessage() != "1")
    {
        Serial.println("Server denied access. Aborting.");

        while (true);
    }

    Serial.println("Connected to the server.");

    // Initialize the hardware control.
    hardwareControl = new HardwareControl(new Controls(), new Heater(), new Motor(), new Water());
    hardwareControl->Initialize();

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
