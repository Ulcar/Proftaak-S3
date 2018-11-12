#include <WiFi.h>

char ssid[] = "12connect";     // the name of your network
int status = WL_IDLE_STATUS;     // the Wifi radio's status

void setup()
{
  Serial.begin(9600);

  Serial.println("Attempting to connect to open network...");
  status = WiFi.begin(ssid);

  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    while(true);
  }
  else {
      Serial.print("Connected to the network");
  }
}

void loop()
{

}
