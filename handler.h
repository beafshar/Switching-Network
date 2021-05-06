#include "headers.h"

class Handler
{
    public:
        Handler();
        void get_input();
        void input_handler();
        void make_new_switch(int number_of_ports, int switch_number);
        void make_new_system(int system_number);
        void connect_system_to_switch(string connect, int system_number, int switch_number);
        void connect_switch_to_switch(string connect, int switch_number_1, int switch_number_2);
        void stp();

    private:
        string current_input;
        map<int, int> system_switches;
        vector<int> child_pid;
};