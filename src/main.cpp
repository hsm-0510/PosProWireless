#include <Arduino.h>
#include "posprowifi_wifi.h"
#include "tcp_cmds.h"
#include "access_point.h"
#include "print_routines.h"

void setup() {
  Serial.begin(115200);
  delay(300);
  Serial.println("\nESP32 TCP Sender");
  
  //Connect with Router (WiFi Router Code):
  //connectWiFi();

  //AccessPoint Connection:
  Serial.println("Setting up AP (Access Point)...");
  init_access_point();

  //Allows re-send after reconnection
  messageSent = false;
}

void loop() {
  //Try to connect with existing DUC-Access-Point
  if (WiFi.status() != WL_CONNECTED && found == false && firstCheck == false)
  {
    connectAP();
    delay(500);
    firstCheck = true;
  }

  //Keep Access Point up (Checks if it isn't then initializes it):
  if (!apEnabled() && found == false)
  {
    init_access_point();
    delay(500);
    return;
  }

  //Establish TCP Connection
  tcp_connect();
  
  delay(2000);

  // Send once per successful session
  if (!messageSent && client.connected()) {

    //Service Station Sales Print Routine:
    defaultPrint();
    
    //delay(1000);
    //printer_test_print();
    //delay(3000);
    //printer_cut_paper();
    
    // Optional: close after sending
    messageSent = true;

    //Closes TCP Connection
    client.stop();
    Serial.println("TCP connection closed.");
  }

  // Small idle delay
  delay(200);
}