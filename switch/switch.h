#ifndef SWITCH_H
#define SWITCH_H

#include "headers.h"
using namespace std;

class Switch
{
    public:
        Switch(int number_of_ports, int switch_number);
        void connect(int system_number, int port_numnbr);
        void send(int system_number_1, int system_number_2);
    private:
        int number_of_ports;
        int switch_number;
        map <int, int> lookup_table;
        vector <int> systems;
};

#endif