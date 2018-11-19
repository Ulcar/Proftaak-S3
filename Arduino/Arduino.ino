#include "hardware/Water.h"
#include "includes/Vector.h"

#include <Centipede.h>
#include <Wire.h>

#include "HardwareControl.h"
/* #include "WifiClient.h" */
#include "SerialClient.h"
#include "Machine.h"

Centipede centipede;
/* WifiClient* client; */
SerialClient* client;

HardwareControl hardwareControl(centipede);

void setup()
{
    Serial.begin(9600);
    Wire.begin();

    // Initialize the hardware control.
    hardwareControl.Initialize();
    hardwareControl.AddInterface(new Water());

    // Connect to the server.
    Serial.println("Connecting to the Wi-Fi network...");

    /* client = new WifiClient("12connect", "192.168.200.73", 1337); */
    client = new SerialClient();

    if (!client->IsConnected())
    {
        Serial.println("Could not connect to the Wi-Fi network. Aborting.");

        while (true);
    }

    Serial.println("Connected to the Wi-Fi network.");
    Serial.println("Connecting to the server...");

    if (!client->Connect())
    {
        Serial.println("Could not connect to the server. Aborting.");

        while (true);
    }

    Serial.println("Connected to the server.");
    Serial.println(client->GetMacAddress());

    Machine machine(hardwareControl, client);

    Vector<Action*> actions;
    actions.push_back(new FillWaterAction(3));
    actions.push_back(new HeatAction(2));

    machine.NewProgram(0, actions);

    machine.StartProgram(0);
}

void loop()
{
}
