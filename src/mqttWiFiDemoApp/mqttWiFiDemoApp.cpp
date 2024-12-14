
#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <./mqttWiFiDemoApp/credentials.h>
#include <./alive/alive.h>
//MQTT
String clientID="ESP32-";
const char* mqtt_server = "192.168.178.36";
const char* mqtt_user="";
const char* mqtt_password="";
WiFiClient espClient;
PubSubClient client(espClient);

const int ledPin = 10; // GPIO10 (D10)

static void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    clientID += String(random(0xffff), HEX);
    if (client.connect(clientID.c_str(), mqtt_user, mqtt_password))
    {
      Serial.println("connect to MQTT");
      client.subscribe("fromNodeRED");
      client.subscribe("ledState");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

static void callback(char *topic, byte *message, unsigned int length)
{
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  if (String(topic) == "fromNodeRED")
  {
    Serial.println(messageTemp);
  }

  else if (String(topic) == "ledState")
  {
    Serial.println(messageTemp);
    ALIVE_Disable(50);
    
    if (messageTemp == "on")
    {      
      digitalWrite(ledPin, HIGH);
    }
    else if (messageTemp == "off")
    {
      digitalWrite(ledPin, LOW);      
    }
  }
}

void mqttWiFiDemoApp_init(void)
{
    enum 
    {
        wifiM_NOT_INITIALIZED,
        wifiM_INITIALIZED
    }wifiM_state = wifiM_NOT_INITIALIZED;

  if (wifiM_state == wifiM_NOT_INITIALIZED)
  {
    Serial.println("Connect to my WIFI");
    WiFi.begin(ssid, password);

    byte cnt = 0;

    while(WiFi.status() != WL_CONNECTED){
        delay(1000);
        Serial.print(".");
        cnt++;

        if(cnt>30){
        ESP.restart();
        }
    } 
    Serial.println(WiFi.localIP());
    wifiM_state = wifiM_INITIALIZED;

    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);    
  }
}

void mqttWiFiDemoApp_backGroundTask(void)
{
  if (!client.connected())
  {
    reconnect();
  }

  if (!client.loop())
  {
    client.connect("ESP32MQTT");
  }  
}

void mqttWiFiDemoApp_cyclicTask100ms(void)
{
  static uint8_t count_down_publish = 0;
  if (! count_down_publish)
  {
    client.publish("toNodeRED", "Hello from ESP32 ");
    count_down_publish = 100u;
  }
  else
  {
    count_down_publish--;
  }
}