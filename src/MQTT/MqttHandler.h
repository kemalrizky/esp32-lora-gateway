#pragma once

#include "Global.h"
#include <PubSubClient.h>
#include "credentials.h"
#include <WiFi.h>


class MqttHandler{
    public:
     void setup();
     bool connect();
     bool publish(String, String);
     void subscribe(String);
     void loop();
     bool isConnected();
    
    private:
     WiFiClient wifiClient;
     PubSubClient mqttClient;
     char * stringToChar(String);
     char * assignMqttClientId();
};

void callback(char *, byte *, unsigned int);