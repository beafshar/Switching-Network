#ifndef SWITCH_H
#define SWITCH_H

#include "headers.h"

class Switch
{
    public:
        Switch(int number_of_ports, int switch_number);
        void connect(int system_number, int port_numnbr);
        void send(int system_number_1, int system_number_2);
        void recieve(int system_number_1, int system_number_2);
        void switch_handler();
    private:
        int number_of_ports;
        int switch_number;
        vector<char*> pipes;
        vector<int> fd;
        map <int, int> lookup_table;
        map <char*, int> file_d;
};

#endif