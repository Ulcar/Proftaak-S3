#include "hardware/Controls.h"
#include "hardware/Heater.h"
#include "hardware/Motor.h"
#include "hardware/Water.h"

#include "HardwareControl.h"
/* #include "WifiClient.h" */
#include "SerialClient.h"
#include "Machine.h"

/* WifiClient* client; */
HardwareControl hardwareControl;
SerialClient* client;

void setup()
{
    Serial.begin(9600);

    // Initialize the hardware control.
    hardwareControl.SetControls(new Controls());
    hardwareControl.SetHeater(new Heater());
    hardwareControl.SetMotor(new Motor());
    hardwareControl.SetWater(new Water());

    hardwareControl.Initialize();

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

    Vector<IAction*> actions;
    actions.push_back(new FillWaterAction(3));
    actions.push_back(new HeatAction(2));

    machine.NewProgram(0, actions);

    machine.StartProgram(0);

    Water* water = hardwareControl.GetWater();
    water->SetDrain(STATE_ON);

    Heater* heater = hardwareControl.GetHeater();
    heater->Set(STATE_ON);

    Controls* controls = hardwareControl.GetControls();
    controls->SetLock(STATE_ON);
    controls->SetSoap(STATE_ON, 1);
    controls->SetSoap(STATE_ON, 2);

    Motor* motor = hardwareControl.GetMotor();
    motor->SetDirection(MD_LEFT);
    motor->SetSpeed(SPEED_LOW);
}

Temperature lastTemperature = TEMP_OFF;
WaterLevel lastWaterLevel = WL_EMPTY;
bool lastPressure = false;

void loop()
{
    Controls* controls = hardwareControl.GetControls();
    Water* water = hardwareControl.GetWater();

    WaterLevel level = water->GetLevel();

    if (level != lastWaterLevel)
    {
        Serial.println("Water Level: " + String(level));

        lastWaterLevel = level;

        if (level == WL_FULL)
        {
            water->SetDrain(STATE_OFF);
            water->SetSink(STATE_ON);

            controls->SetSoap(STATE_OFF, 1);
            controls->SetSoap(STATE_OFF, 2);
        }

        if (level == WL_EMPTY)
        {
            water->SetSink(STATE_OFF);
            water->SetDrain(STATE_ON);

            controls->SetSoap(STATE_ON, 1);
            controls->SetSoap(STATE_ON, 2);
        }
    }

    Heater* heater = hardwareControl.GetHeater();
    Temperature temperature = heater->GetTemperature();

    if (temperature != lastTemperature)
    {
        Serial.println("Temperature: " + String(temperature));

        lastTemperature = temperature;

        if (temperature == TEMP_HOT)
        {
            heater->Set(STATE_OFF);
        }

        if (temperature == TEMP_OFF)
        {
            heater->Set(STATE_ON);
        }
    }

    bool pressure = water->HasPressure();

    if (pressure != lastPressure)
    {
        Serial.println("Pressure: " + String(pressure ? "yes" : "no"));

        lastPressure = pressure;
    }
}
