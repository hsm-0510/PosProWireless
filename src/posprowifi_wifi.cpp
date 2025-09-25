#include <Arduino.h>
#include <WiFi.h>
#include "posprowifi_wifi.h"

//WiFi Test SSID and Password (discontinued)
const char* WIFI_SSID = "tech-wifi";
const char* WIFI_PASSWORD = "abcdefg12345";

WiFiClient client;

void connectWiFi(const char* connection_ssid, const char* connection_password) {
  if (WiFi.status() == WL_CONNECTED) return;

  Serial.print("Connecting to Wi-Fi: ");
  Serial.print(connection_ssid);
  Serial.println(" ...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(connection_ssid, connection_password);

  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 15000) { // 15s
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWi-Fi connected ✅");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("RSSI: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
  } else {
    Serial.println("\nWi-Fi connect failed ❌ (will retry)");
  }
}