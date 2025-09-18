#include <Arduino.h>
#include <Wifi.h>
#include <tcp_cmds.h>

//TCP/IP Ip.Address and Port
const char* TCP_HOST = "192.168.0.95";
const uint16_t TCP_PORT = 9100;

//TCP handling
volatile bool messageSent = false;
unsigned long lastAttemptMs = 0;
const unsigned long RETRY_MS = 5000;

//Thermal Printer Commands
const char* PRINTER_MSG = "T: 23.5C; A: 160000.00 l/m; F: 1800 rpm\nT: 23.5C; A: 160000.00 l/m; F: 1800 rpm\n";
const uint8_t printer_cut_paper_cmd[] = {
    0x1D, 
    'V', 
    'B', 
    0x00, 
    '\n', 
    '\n', 
    0x00
  };
const uint8_t printer_test_print_cmd[] = {
    0x1F, 
    0x1B, 
    0x1F, 
    'g', 
    0x00
  };

void tcp_connect(){
    if (!client.connected() && messageSent == false) {
    if (millis() - lastAttemptMs >= RETRY_MS) {
      lastAttemptMs = millis();
      Serial.printf("Connecting to %s:%u ...\n", TCP_HOST, TCP_PORT);
      if (client.connect(TCP_HOST, TCP_PORT)) {
        Serial.println("TCP connected ✅");
      } else {
        Serial.println("TCP connect failed ❌ (will retry)");
      }
    }
    return;
  }
}

//Printing Message
void printer_print_msg(const char* cmd){
    size_t toWrite = strlen(cmd);
    size_t written = client.write((const uint8_t*)cmd, toWrite);
    Serial.printf("Sent %u/%u bytes: %s\n", (unsigned)written, (unsigned)toWrite, cmd);
}

//Cutting Paper
void printer_cut_paper(){
    client.write("\n", sizeof("\n"));
    client.write(printer_cut_paper_cmd, sizeof(printer_cut_paper_cmd));
    Serial.printf("Data sent");
}

//Printer Self Test
void printer_test_print(){
    client.write("\n", sizeof("\n"));
    client.write(printer_test_print_cmd, sizeof(printer_test_print_cmd));
    Serial.printf("Data sent");
}
