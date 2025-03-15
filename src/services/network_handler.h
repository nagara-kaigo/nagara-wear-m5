#ifndef NETWORK_HANDLER_H
#define NETWORK_HANDLER_H

#include <Arduino.h>
#include <WiFiClientSecure.h>

class NetworkHandler {
public:
    NetworkHandler();
    bool sendHttpPostRequest(const String& url, const String& headers, const String& body, String& response);
    
private:
    WiFiClientSecure client;
};

#endif
