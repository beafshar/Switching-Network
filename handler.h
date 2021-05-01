#include "headers.h"
#include "switch.h"
#include "system.h"

class Handler
{
    public:
        Handler();
        void get_input();
        void input_handler();
        void make_new_switch(int number_of_ports, int switch_number);
        void make_new_system(int system_number);
        void connect_system_to_switch(int system_number, int switch_number, int port_number);
    private:
        string current_input;
        vector<vector<int>> switch_file_discriptors;
        vector<vector<int>> system_file_discriptors;
        vector<int> switches;
        vector<int> systems;
};