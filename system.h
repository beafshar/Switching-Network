#ifndef SYSTEM_H
#define SYSTEM_H

#include "headers.h"

class System
{
    public:
        System(int system_number, string my_pipe);
        void connect(int s_number, int p_number);
        void send();
        void recieve(string data);
        void system_handler();
    private:
        char* pipe;
        int system_number;
        int port;
        int switch_number;
        int fram_size;
};


#endif