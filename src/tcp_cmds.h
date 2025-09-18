#pragma once
#include <stdint.h>
#include <posprowifi_wifi.h>

//TCP/IP Ip.Address and Port
extern const char* TCP_HOST;
extern const uint16_t TCP_PORT;

//TCP handling
extern volatile bool messageSent;
extern unsigned long lastAttemptMs;
extern const unsigned long RETRY_MS;

//Thermal Printer Commands
extern const char* PRINTER_MSG;
extern const uint8_t printer_cut_paper_cmd[];
extern const uint8_t printer_test_print_cmd[];

//Printer Functions
void tcp_connect();
void printer_print_msg(const char* cmd);
void printer_cut_paper();
void printer_test_print();