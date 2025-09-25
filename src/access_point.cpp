#include <Arduino.h>
#include <WiFi.h>
#include <access_point.h>
#include <posprowifi_wifi.h>
#include <ESP32Ping.h>

//Master Access Point
const char* ap_ssid = "DUC-Access-Point";
const char* ap_password = "123456789";

//Slave Access Point
const char* TARGET_WIFI_SSID = "DUC-Access-Point";
const char* TARGET_WIFI_PASSWORD = "123456789";

//Slave DUC Device IP Addresses
IPAddress TARGET1(192, 168, 0, 56);
IPAddress TARGET2(192, 168, 0, 57);
IPAddress TARGET3(192, 168, 0, 58);
IPAddress TARGET4(192, 168, 0, 59);

//Sets web server port number to 80
WiFiServer server(80);

//Existing DUC Access Point check
bool found = false;
bool firstCheck = false;

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

//Connects to existing DUC Access Point Available (if exists, then find free host id: 56, 57, 58, or 59. If doesn't exist, then leave)
void connectAP()
{
  if (WiFi.status() == WL_CONNECTED) return;
  if (WiFi.status() != WL_CONNECTED && found == true)
  {
    connectWiFi(TARGET_WIFI_SSID, TARGET_WIFI_PASSWORD);
    delay(500);
    return;
  }
  
  Serial.print("Looking for DUC Access Point: ");
  Serial.println(TARGET_WIFI_SSID);
  
  //Scan: Synchronous, including hidden SSIDs
  int n = WiFi.scanNetworks(false, true); // Asynchronous: False, Show Hidden: True
  Serial.printf("Scanned Wifi Network and Found %d \n", n);
  if (n <= 0)
  {
    Serial.println("No Networks Found \n");
  }
  else
  {
    Serial.printf("Found %d Networks \n", n);
  }

  //Finding DUC-Access-Point from scanned SSIDs
  for (int i = 0; i < n; i++)
  {
    String ssid = WiFi.SSID(i);
    if (ssid == TARGET_WIFI_SSID)
    {
      found = true;
      Serial.printf("Found \"%s\" RSSI=%d dBm CH=%d BSSID=%s ENC=%d\n",
      TARGET_WIFI_SSID, WiFi.RSSI(i), WiFi.channel(i), WiFi.BSSIDstr(i).c_str(), (int)WiFi.encryptionType(i));
      break;
    }
  }

  //Connect with DUC Access Point if exists, if doesn't exist then exit this function.
  if (found == true)
  {
    connectWiFi(TARGET_WIFI_SSID, TARGET_WIFI_PASSWORD);
    delay(500);
    return;
  }
  else
  {
    return;
  }
////Pinging for available DUC devices to setup standardized IP (discontinued, might use espNow later)
//   if (WiFi.status() == WL_CONNECTED)
//   {
//     Serial.print("WiFi OK. My IP: ");
//     Serial.println(WiFi.localIP());
//     Serial.print("Pinging ");
//     Serial.println(TARGET1);

//     //Pinging for free host id
//     const byte count = 4;

//     int replies = 0;
//     unsigned long tmin = ULONG_MAX, tmax = 0, tsum = 0;

//     for (byte i = 0; i < count; ++i)
//     {
//         unsigned long t0 = millis();
//         bool ok = Ping.ping(TARGET1, 1);   // <-- only 2 args in this library
//         unsigned long rtt = millis() - t0;

//         if (ok)
//         {
//             replies++;
//             if (rtt < tmin) tmin = rtt;
//             if (rtt > tmax) tmax = rtt;
//             tsum += rtt;
//         }
//         else
//         {
//             unsigned long t0 = millis();
//             bool ok = Ping.ping(TARGET2, 1);   // <-- only 2 args in this library
//             unsigned long rtt = millis() - t0;

//             if (ok)
//             {
//                 replies++;
//                 if (rtt < tmin) tmin = rtt;
//                 if (rtt > tmax) tmax = rtt;
//                 tsum += rtt;
//             }
//             else
//             {
//                 unsigned long t0 = millis();
//                 bool ok = Ping.ping(TARGET3, 1);   // <-- only 2 args in this library
//                 unsigned long rtt = millis() - t0;

//                 if (ok)
//                 {
//                     replies++;
//                     if (rtt < tmin) tmin = rtt;
//                     if (rtt > tmax) tmax = rtt;
//                     tsum += rtt;
//                 }
//                 else
//                 {
//                     unsigned long t0 = millis();
//                     bool ok = Ping.ping(TARGET4, 1);   // <-- only 2 args in this library
//                     unsigned long rtt = millis() - t0;

//                     if (ok)
//                     {
//                         replies++;
//                         if (rtt < tmin) tmin = rtt;
//                         if (rtt > tmax) tmax = rtt;
//                         tsum += rtt;
//                     }
//                     else
//                     {

//                     }
//                 }
//             }
//         }
//         delay(200);
//     }

//     if (replies > 0)
//     {
//         unsigned long avg = tsum / replies;
//         Serial.printf("Replies: %d/%d | min=%lu ms avg=%lu ms max=%lu ms\n",
//                         replies, count, tmin, avg, tmax);
//     }
//     else
//     {
//         Serial.println("Host unreachable (no replies).");
//     }
}