#include <Arduino.h>
#include "posprowifi_wifi.h"
#include "tcp_cmds.h"
#include "access_point.h"

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
  
  // Keep Wi-Fi up (WiFi Router Code)
  // if (WiFi.status() != WL_CONNECTED) {
  //   connectWiFi();
  //   delay(500);
  //   return;
  // }

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
    printer_format(initialize);
    //printer_format(codepage_0);
    //printer_format(default_line_spacing);
    printer_format(bold_on);
    printer_format(center);
    //printer_format(bold_doubleHW);
    printer_print_msg(title);
    printer_format(bold_off);
    printer_format(normal_size);
    printer_print_msg(station_name);
    printer_format(bold_off);
    printer_print_msg(station_address);
    printer_format(bold_on);
    printer_print_msg(original);
    printer_format(bold_off);
    printer_format(left_align);
    printer_print_msg(receipt_id);
    printer_print_msg(crnt_date);
    printer_print_msg(crnt_time);
    printer_print_msg(trx_id);
    printer_print_msg(trx_type);
    printer_print_msg(dispenser_id);
    printer_print_msg(nozzle_no);
    printer_print_msg(product);
    printer_print_msg(vehicle_no);
    printer_print_msg(mobile_no);
    printer_print_msg(price);
    printer_print_msg(qty);
    printer_print_msg(sale);
    printer_format(center);
    printer_print_msg(conclusion);
    delay(1000);
    printer_cut_paper();
    
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