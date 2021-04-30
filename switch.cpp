#include "switch.h"

Switch::Switch(int number_of_ports, int switch_number)
{
    number_of_ports = number_of_ports;
    switch_number = switch_number;
}

void Switch::connect(int system_number, int port_numnbr)
{
    systems.push_back(system_number);
    lookup_table.insert({system_number,port_numnbr});
    return;
}

void Switch::send(int system_number_1, int system_number_2)
{
    return;
}