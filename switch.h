#ifndef SWITCH_H
#define SWITCH_H

#include "headers.h"

class Switch
{
    public:
        Switch(int number_of_ports, int switch_number, string named_pipe);
        void connect(int system_number, int port_numnbr);
        void connect_to_switch(int snum_1, int pnum_1, int snum_2, int pnum_2);
        void send(int system_number_1, int system_number_2);
        void recieve(int system_number_1, int system_number_2);
        void switch_handler();
        void listen_to_parrent();
        void broadcast(char* data);
    private:
        int number_of_ports;
        int switch_number;
        string pipe;
        vector<string> pipes;
        vector<int> fd;
        map <int, int> lookup_table;
        map <int,string> file_d;
        map <int,int> switch_port;
        map <int,int> switch_switch;
        int frame_size;
};

#endif