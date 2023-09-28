#pragma once

#include "Global.h"
#include "credentials.h"

class InternetHandler{
    public:
     void wifiSetup();
     void initConnect();
     bool connect();
     bool isConnected();
};

#include <WiFi.h>