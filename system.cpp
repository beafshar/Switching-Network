#include "system.h"

System::System(int system_number, int read_fd)
{
    system_number = system_number;
    unnamed_pipe = read_fd;
}

void System::connect(int system_number, int switch_number, int port_number)
{
    return;
}
void System::send(int system_number_1, int system_number_2, string data)
{
    return;
}
void System::recieve(string data)
{
    return;
}