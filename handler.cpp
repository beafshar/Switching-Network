#include "handler.h"

Handler::Handler(){}

void Handler::get_input()
{
    getline(cin, current_input);
}

void Handler::input_handler()
{
    vector <string> tokens;
    stringstream check1(current_input); 
    string intermediate;

    while(getline(check1, intermediate, ' '))
        tokens.push_back(intermediate); 

    if (tokens[0].compare("MySwitch") == 0)
        make_new_switch(stoi(tokens[1]), stoi(tokens[2]));

    if (tokens[0].compare("‫‪MySystem‬‬") == 0)
        make_new_system(stoi(tokens[1]));
    
    if (tokens[0].compare("Connect") == 0)
        connect_system_to_switch(current_input, stoi(tokens[1]), stoi(tokens[2]), stoi(tokens[3]));
}

void Handler::make_new_switch(int number_of_ports, int switch_number)
{
    
    pid_t p;
    p = fork();
    if (p<0)
    {
        fprintf(stderr, "fork Failed" );
        return;
    }
    else if (p > 0)
    {
        switches.push_back(switch_number);
    }
    else
    {
        Switch s(number_of_ports, switch_number);
        s.switch_handler();
    }
}

void Handler::make_new_system(int system_number)
{
    pid_t p;
    p = fork();
    if (p<0)
    {
        fprintf(stderr, "fork Failed" );
        return;
    }
    else if (p > 0)
    {
        systems.push_back(system_number);
    }
    else
    {
        System s(system_number);
    }
}

void Handler::connect_system_to_switch(string connect, int system_number, int switch_number, int port_number)
{
    string name = "switch " + to_string(switch_number) + " " + to_string(port_number);
    char* pipe;
    string str_obj(name);
    pipe = &str_obj[0];
    int fd = open(pipe, O_WRONLY);
    const char *pchar = connect.c_str();
    char inp[100];
    strcpy(inp, pchar);
    write(fd,inp,strlen(inp));
    close(fd);
    return;
}