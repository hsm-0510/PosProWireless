#include <Arduino.h>
#include "tcp_cmds.h"
//Service Station Sales Print Routine (future-work: pass variables in argument for actual print values)
void defaultPrint()
{
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
}