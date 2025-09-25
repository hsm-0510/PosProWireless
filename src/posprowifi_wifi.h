#pragma once
#include <WiFi.h>

//WiFi test ssid and password (discontinued)
extern const char* WIFI_SSID;
extern const char* WIFI_PASSWORD;

extern WiFiClient client;

//Connecting with a WiFi Network
void connectWiFi(const char* connection_ssid, const char* connection_password);