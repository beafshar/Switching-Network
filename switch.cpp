#include "switch.h"

Switch::Switch(int number_of_ports, int switch_number, int file_d[2])
{
    number_of_ports = number_of_ports;
    switch_number = switch_number;
    fd[0] = file_d[0];
    fd[1] = file_d[1];
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