#include <Arduino.h>
#include <WiFi.h>
#include <tcp_cmds.h>

//TCP/IP Ip.Address and Port
const char* TCP_HOST = "192.168.0.95";
const uint16_t TCP_PORT = 9100;

//TCP handling
volatile bool messageSent = false;
unsigned long lastAttemptMs = 0;
const unsigned long RETRY_MS = 5000;

//const char* PRINTER_MSG = "T: 23.5C; A: 160000.00 l/m; F: 1800 rpm\nT: 23.5C; A: 160000.00 l/m; F: 1800 rpm\n";

//Thermal Printer - Formatting Commands
const uint8_t initialize[] =
{
  0x1B,
  0x40
};
const uint8_t codepage_0[] = 
{
  0x1B,
  0x74,
  0x00
};
const uint8_t default_line_spacing[] = 
{
  0x1B,
  0x32
};
const uint8_t center[] = 
{
  0x1B,
  0x61,
  0x01
};
const uint8_t bold_doubleHW[] =
{
  0x1B,
  0x21,
  0x38
};
const uint8_t bold_on[] = 
{
  0x1B,
  0x45,
  0x01
};
const uint8_t double_height_width[] = 
{
  0x1D,
  0x21,
  0x11
};
const uint8_t normal_size[] = 
{
  0x1B,
  0x21,
  0x00
};
const uint8_t bold_off[] = 
{
  0x1B,
  0x45,
  0x00
};
const uint8_t left_align[] = 
{
  0x1B,
  0x61,
  0x00
};

//Thermal Printer - Print Variables
const char* title = "\r\nPSO\r\n";
const char* station_name = "\r\nKARACHI SERVICE STATION\r\n";
const char* station_address = "\r\nSAFA STATION, MEHRAN TOWN, KORANGI\r\nINDUSTRIAL AREA, KARACHI, PAKISTAN\r\n\n";
const char* original = "\r\nORIGINAL\r\n\n";
const char* receipt_id  =  "Receipt ID    : 30696759\r\n";
const char* crnt_date   = "Date           : 18/09/2025\r\n";
const char* crnt_time   = "Time           : 13:05\r\n";
const char* trx_id      = "TRX. ID        : 41730866\r\n";
const char* trx_type    = "TRX. TYPE      : Cash\r\n";
const char* dispenser_id = "Dispenser ID   : PSO-002\r\n";
const char* nozzle_no  = "Nozzle. No     : A1\r\n";
const char* product     = "Product        : Premium\r\n";
const char* vehicle_no  = "Vehicle No.    : Not Entered\r\n";
const char* mobile_no   = "Mobile No.     : Not Entered\r\n";
const char* price       = "Price          : PKR 256\r\n";
const char* qty         = "Quantity       : 3.5 Ltr\r\n";
const char* sale        = "Sale           : PKR 896\r\n\n\n";
const char* conclusion  = "\r\nThank You! Visit Again\r\nSave Fuel, Save Money\r\n\n\n";

//Thermal Printer - Operational Commands
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

//TCP Connection Function
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

//Formatting Command
void printer_format(const uint8_t* format_cmd)
{
  client.write(format_cmd, sizeof(format_cmd));
  Serial.printf("Format Adjustment Sent");
}