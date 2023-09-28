#include "LoRaHandler.h"

void LoRaHandler::setup() {
    LoRa.setPins(PIN_LORA_SS, PIN_LORA_RST, PIN_LORA_DIO0);
}

bool LoRaHandler::connect() {
    if(!LoRa.begin(freq)) {
        Serial.println("LoRa initialization failed, try again later");
        isConnected =  false;
        return false;
    }
    else {
        Serial.println("LoRa initialiazation succes");
        isConnected =  true;
        return true;
    }
}

void LoRaHandler::disconnect() {
    LoRa.end();
}

void LoRaHandler::receiveMode() {
    LoRa.disableInvertIQ();               // normal mode
    LoRa.receive();                       // set receive mode
}

int LoRaHandler::parsePacket() {
    int _packetSize = LoRa.parsePacket();
    return _packetSize;
}

bool LoRaHandler::receiveMsg(int _packetSize) {
    if (_packetSize == 0) return false;

    // read packet header bytes:
    recipientId = LoRa.read();
    senderId = LoRa.read();
    msgId = LoRa.read();
    msgLength = LoRa.read();

    incomingMsg = "";

    while (LoRa.available()) {
        incomingMsg += (char)LoRa.read();
    }

    if (msgLength != incomingMsg.length()) {
        Serial.println("error: message length does not match length");
        return false;
    }

    if (recipientId != localAddress) {
    Serial.println("This message is not for this gateway.");
    return false;
    }

    Serial.printf("Gateway receive: %s", incomingMsg);
    return true;
}

String LoRaHandler::getMessage() {
    String _message = incomingMsg;
    return _message;
}

String LoRaHandler::getTopic() {
    StaticJsonDocument<200> receivedJson;
    DeserializationError error = deserializeJson(receivedJson, incomingMsg);

    String _device;
    if(!error) {
        _device = receivedJson["device"].as<String>();
    }
    else {
        Serial.println("Failed to get topic from payload");
    }

    String _topic = "IoTDevices/" + _device;
}
