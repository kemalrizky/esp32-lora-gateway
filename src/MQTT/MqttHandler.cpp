#include "MqttHandler.h"

const char *mqttServer = MQTT_SERVER;


void callback(char* _topic, byte* _payload, unsigned int _length) {
    Serial.print("Message arrived on topic: ");
    Serial.print(_topic);
    Serial.print(". Message: ");
    String _message;
    
    for (int i = 0; i < _length; i++) {
        Serial.print((char)_payload[i]);
        _message += (char)_payload[i];
    }
    
    Serial.println();
}

char * MqttHandler::stringToChar(String _string) {
    char* _charBuffer = new char[_string.length() + 1]; // +1 for the null terminator
    _string.toCharArray(_charBuffer, _string.length() + 1);
    return _charBuffer;
    
}

char * MqttHandler::assignMqttClientId() {
    randomSeed(millis());
    String _clientIdStr = "LoRaGateway" + String(random(1, 1001));
    char* _clientIdChar = stringToChar(_clientIdStr);
    return _clientIdChar;
}

void MqttHandler::setup() {
    mqttClient.setClient(wifiClient);
}

bool MqttHandler::connect() {
    Serial.print("\nAttempting MQTT connection...");

    char *clientId = assignMqttClientId();

    if (mqttClient.connect(clientId)) {         
      Serial.println("connected");
      return true;
    } 
    else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 1 seconds");
      return false;
    }
}

void MqttHandler::subscribe(String _topic) {
    char *_topicChar = stringToChar(_topic);
    mqttClient.subscribe(_topicChar);
}

void MqttHandler::loop() {
    mqttClient.loop();
}

bool MqttHandler::publish(String _topic, String _payload) {
    char *_payloadChar = stringToChar(_payload);

    char *_topicChar = stringToChar(_topic);

    if (mqttClient.publish(_topicChar, _payloadChar)) {   
      Serial.println("\nData published.");
      return true;
    } 
    else {
      Serial.print("failed to publish, rc=");
      Serial.print(mqttClient.state());
      return false;
    }
}

bool MqttHandler::isConnected() {
    if(!mqttClient.connected()) {
        Serial.println("Not connected to MQTT broker");
        return false;
    }
    else {
        Serial.println("Connected to MQTT broker");
        return true;
    }
}