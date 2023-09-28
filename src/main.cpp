#include "Global.h"
#include "LoRa\LoRaHandler.h"
#include "MQTT\InternetHandler.h"
#include "MQTT\MqttHandler.h"
#include "OTA\OtaHandler.h"

LoRaHandler loRaHandler;
InternetHandler internetHandler;
MqttHandler mqttHandler;
OtaHandler otaHandler;


void setup() {
  Serial.begin(115200);
  loRaHandler.setup();
  internetHandler.wifiSetup();
  mqttHandler.setup();

  loRaHandler.connect();
  loRaHandler.receiveMode();

  otaHandler.init();
  
}

void loop() {
  if(loRaHandler.isConnected) {
    loRaHandler.receiveMsg(loRaHandler.parsePacket());
  }
  else {
    loRaHandler.disconnect();
    loRaHandler.connect();
  }

  if(!mqttHandler.isConnected()) {
    if(!internetHandler.isConnected()) {
      internetHandler.connect();
    }
    mqttHandler.connect();
  }

  mqttHandler.loop();

  if(mqttHandler.isConnected() && loRaHandler.receiveMsg(loRaHandler.parsePacket())) {
    mqttHandler.publish(loRaHandler.getTopic(), loRaHandler.getMessage());
  }

  otaHandler.handleReq();
}
