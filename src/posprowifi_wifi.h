#pragma once
#include <WiFi.h>

extern const char* WIFI_SSID;
extern const char* WIFI_PASSWORD;

extern WiFiClient client;

void connectWiFi();