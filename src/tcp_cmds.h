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


//Thermal Printer - Formatting Commands
extern const uint8_t initialize[];
extern const uint8_t codepage_0[];
extern const uint8_t default_line_spacing[];
extern const uint8_t bold_doubleHW[];
extern const uint8_t center[];
extern const uint8_t bold_on[];
extern const uint8_t double_height_width[];
extern const uint8_t normal_size[];
extern const uint8_t bold_off[];
extern const uint8_t left_align[];

//Thermal Printer - Print Variables
extern const char* title;
extern const char* station_name;
extern const char* station_address;
extern const char* original;
extern const char* receipt_id;
extern const char* crnt_date;
extern const char* crnt_time;
extern const char* trx_id;
extern const char* trx_type;
extern const char* dispenser_id;
extern const char* nozzle_no;
extern const char* product;
extern const char* vehicle_no;
extern const char* mobile_no;
extern const char* price;
extern const char* qty;
extern const char* sale;
extern const char* conclusion;

//Thermal Printer - Operational Commands
extern const char* PRINTER_MSG;
extern const uint8_t printer_cut_paper_cmd[];
extern const uint8_t printer_test_print_cmd[];

//Printer Functions
void tcp_connect();
void printer_print_msg(const char* cmd);
void printer_cut_paper();
void printer_test_print();
void printer_format(const uint8_t* format_cmd);