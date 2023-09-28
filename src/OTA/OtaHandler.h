#pragma once

#include "Global.h"
#include <WebServer.h>
#include <ESP2SOTA.h>

class OtaHandler {
    public:
     void init();
     void handleReq();
};
