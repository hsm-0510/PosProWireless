#include <Arduino.h>
#include "posprowifi_wifi.h"
#include "tcp_cmds.h"

void setup() {
  Serial.begin(115200);
  delay(300);
  Serial.println("\nESP32 TCP Sender");
  connectWiFi();
  messageSent = false; // allow re-send after reconnection
}

void loop() {
  // Keep Wi-Fi up
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
    delay(500);
    return;
  }

  //Establish TCP Connection
  tcp_connect();
  
  delay(2000);

  // Send once per successful session
  if (!messageSent && client.connected()) {
    //Test Routine
    for (int i = 0; i < 10; i++)
    {
      printer_print_msg(PRINTER_MSG);
    }
    delay(1000);
    printer_cut_paper();
    delay(1000);
    printer_test_print();
    delay(3000);
    printer_cut_paper();
    
    // Optional: close after sending
    messageSent = true;
    client.stop();
    Serial.println("TCP connection closed.");
  }

  // Small idle delay
  delay(200);
}