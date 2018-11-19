#include "hardware/Water.h"

#include "HardwareControl.h"
#include "WifiClient.h"

HardwareControl hardwareControl;
WifiClient* client;

void setup()
{
    Serial.begin(9600);

    hardwareControl.AddInterface(new Water());

    Serial.println("Connecting to the Wi-Fi network...");

    client = new WifiClient("12connect", "192.168.200.73", 1337);

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

    // Temporary HAL test.
    Water* water = (Water*) hardwareControl.GetInterface("water");
    Serial.println(String(water->GetLevel()));
}

void loop()
{
}
