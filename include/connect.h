#include <Arduino.h>
#include <WiFiClient.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "config.h"

WiFiClient espClient;
PubSubClient client(espClient);

void connectToWifi()
{

    WiFi.begin(ssid, password);

    int connectionAttempts = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        if (connectionAttempts > 150)
        {
            //after failing to connect for 150 times, put microcontroller to sleep for 5 minutes.
            //when wakes up, will reboot and try to connect again
            esp_sleep_enable_timer_wakeup(5 * 60 * 1000000);
            esp_deep_sleep_start();
        }
        connectionAttempts++;
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void connectToMqtt()
{
    /* Loop until reconnected */
    while (!client.connected())
    {
        client.setServer(mqtt_server, mqtt_port);
        Serial.print("MQTT connecting ...");
        /* client ID */
        String clientId = mqtt_client_id;
        /* connect now */
        if (client.connect(clientId.c_str(), mqtt_user, mqtt_password))
        {
            Serial.println("connected");
            /* subscribe topic with default QoS 0*/
            //      client.subscribe(LED_TOPIC);
        }
        else
        {
            Serial.print("failed, status code =");
            Serial.print(client.state());
            Serial.println("try again in 5 seconds");
            /* Wait 5 seconds before retrying */
            delay(5000);
        }
    }
}

void ensure_connection(){
    if (WiFi.status() != WL_CONNECTED)
    {
        connectToWifi();
    }
    else if (!client.connected())
    {
        connectToMqtt();
    }
}
