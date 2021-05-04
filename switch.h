#ifndef SWITCH_H
#define SWITCH_H

#include "headers.h"

class Switch
{
    public:
        Switch(int number_of_ports, int switch_number, int read_fd);
        void connect(int system_number, int port_numnbr);
        void send(int system_number_1, int system_number_2);
        void recieve(int system_number_1, int system_number_2);
        void switch_handler();
        void listen_to_parrent(fd_set fds);
        void listen_to_fifo(fd_set fds, int maxfd);
    private:
        int number_of_ports;
        int switch_number;
        int unnamed_pipe;
        vector<string> pipes;
        vector<int> fd;
        map <int, int> lookup_table;
        map <string, int> file_d;
};

#endif