#ifndef SWITCH_H
#define SWITCH_H

#include "headers.h"

class Switch
{
    public:
        Switch(int number_of_ports, int switch_number, int file_d[2]);
        void connect(int system_number, int port_numnbr);
        void send(int system_number_1, int system_number_2);
        int get_switch_number() {return switch_number;}
    private:
        int number_of_ports;
        int switch_number;
        int fd[2];
        map <int, int> lookup_table;
        vector <int> systems;
};

#endif