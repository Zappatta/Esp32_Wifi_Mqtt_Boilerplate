#include <Arduino.h>
#include "connect.h"


void mqtt_callback(char *topic, byte *payload, unsigned int length){

}

void setup()
{
  Serial.begin(115200);
      // put your setup code here, to run once:
  connectToWifi();
  connectToMqtt();
}

void loop() {
  // put your main code here, to run repeatedly:
}