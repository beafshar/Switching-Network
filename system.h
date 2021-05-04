#ifndef SYSTEM_H
#define SYSTEM_H

#include "headers.h"

class System
{
    public:
        System(int system_number, int fd_read);
        void connect(int system_number, int switch_number, int port_number);
        void send(int system_number_1, int system_number_2, string data);
        void recieve(string data);
    private:
        int unnamed_pipe;
        int system_number;
        int port;
        int switch_number;
        int fram_size;
};


#endif