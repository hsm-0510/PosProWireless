#include <Arduino.h>
#include <WiFi.h>
#include <access_point.h>

const char* ap_ssid = "DUC-Access-Point";
const char* ap_password = "123456789";

//Sets web server port number to 80
WiFiServer server(80);

//Initialize Access Point
void init_access_point()
{
    //Configuration of Access Point
    IPAddress apIP(192, 168, 0, 55);
    IPAddress subnetMask(255, 255, 255, 0);
    IPAddress gatewayIP(192, 168, 0, 1);

    //Set up DUC to Access Point mode
    WiFi.mode(WIFI_AP);

    //Configuring AP to defined static IP, gateway, subnetmask
    WiFi.softAPConfig(apIP, gatewayIP, subnetMask);

    //Start the access point with the defined SSID and Password
    WiFi.softAP(ap_ssid, ap_password);

    //IP-Address and Access Point Print
    IPAddress myIP = WiFi.softAPIP();
    Serial.println("AP IP Address: ");
    Serial.println(myIP);
}

//Binary funciton to check AP Status
bool apEnabled()
{
    wifi_mode_t m = WiFi.getMode();
    return (m == WIFI_AP || m == WIFI_AP_STA);
}