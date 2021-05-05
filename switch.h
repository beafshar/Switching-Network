#ifndef SWITCH_H
#define SWITCH_H

#include "headers.h"

class Switch
{
    public:
        Switch(int number_of_ports, int switch_number, string named_pipe);
        void connect(int system_number, int port_numnbr);
        void send(int system_number_1, int system_number_2);
        // void recieve(int system_number_1, int system_number_2);
        void switch_handler();
        void listen_to_parrent();
        // void broadcast(char* data);
    private:
        int number_of_ports;
        int switch_number;
        char* pipe;
        vector<string> pipes;
        vector<int> fd;
        map <int, int> lookup_table;
        map <int,string> file_d;
};

#endif