#pragma once
#include <WiFi.h>

extern const char* ap_ssid;
extern const char* ap_password;

//Initializes Access Point:
extern void init_access_point();

//Checks if AP is enabled
extern bool apEnabled();