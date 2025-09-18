#include <Arduino.h>
#include <WiFi.h>
#include "posprowifi_wifi.h"

const char* WIFI_SSID = "tech-wifi";
const char* WIFI_PASSWORD = "abcdefg123456";

WiFiClient client;

void connectWiFi() {
  if (WiFi.status() == WL_CONNECTED) return;

  Serial.print("Connecting to Wi-Fi: ");
  Serial.print(WIFI_SSID);
  Serial.println(" ...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

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