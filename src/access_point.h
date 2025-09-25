#pragma once
#include <WiFi.h>

//Master Access Point
extern const char* ap_ssid;
extern const char* ap_password;

//Slave Access Point 
extern const char* TARGET_WIFI_SSID;
extern const char* TARGET_WIFI_PASSWORD;

//Existing DUC Access Point check
extern bool found;
extern bool firstCheck;

//Slave DUC Device IP Addresses
extern IPAddress TARGET1;
extern IPAddress TARGET2;
extern IPAddress TARGET3;
extern IPAddress TARGET4;

//Initializes Access Point:
extern void init_access_point();

//Checks if AP is enabled
extern bool apEnabled();

//Connects with existing DUC Access Point
extern void connectAP();