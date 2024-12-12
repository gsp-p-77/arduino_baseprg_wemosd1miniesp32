
#include <Arduino.h>
#include <stdint.h>
#include <stdio.h>
#include <WiFi.h>
#include <./wifiM/credentials.h>

void wifiM_init(void)
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
  }
}
