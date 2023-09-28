#pragma once

#include "Global.h"
#include <SPI.h>
#include <LoRa.h>
#include <ArduinoJson.h>
#include "lora_module_config.h"

class LoRaHandler {
    public:
     void setup();
     bool connect();
     void disconnect();
     void receiveMode();
     bool receiveMsg(int);
     String getMessage();
     String getTopic();
     int parsePacket();
     bool isConnected = false;

    private:
     const long freq = 433E6;
     const byte localAddress = 0xCC;
     byte recipientId;
     byte senderId;
     byte msgId;
     byte msgLength;
     String incomingMsg;
};