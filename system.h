#ifndef SYSTEM_H
#define SYSTEM_H

#include "headers.h"

class System
{
    public:
        System(int system_number, string my_pipe);
        void connect(int s_number, int p_number);
        void send();
        void recieve();
        void system_handler();
        void get_command();
        void recieve_data();
        
    private:
        string pipe;
        int system_number;
        int port;
        int switch_number;
        int frame_size;
};

void sig_handler(int signum);

#endif