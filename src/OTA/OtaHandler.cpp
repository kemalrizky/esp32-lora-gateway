#include "OtaHandler.h"

WebServer server(80);

void OtaHandler::init() {
    delay(1000);
    ESP2SOTA.begin(&server);
    server.begin();
}

void OtaHandler::handleReq() {
    server.handleClient();                // Handle update requests
}