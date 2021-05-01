#include "system.h"

System::System(int system_number, int file_d[2])
{
    system_number = system_number;
    fd[0] = file_d[0];
    fd[1] = file_d[1];
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