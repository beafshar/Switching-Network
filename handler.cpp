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
    
    if (tokens[0].compare("MySystem") == 0)
        make_new_system(stoi(tokens[1]));
    
    if (tokens[0].compare("Connect") == 0)
        connect_system_to_switch(current_input, stoi(tokens[1]), stoi(tokens[2]));

    if (tokens[0].compare("Send") == 0 || tokens[0].compare("Recieve") == 0)
        connect_system_to_switch(current_input, stoi(tokens[1]), system_switches[stoi(tokens[1])]);
    
}

void Handler::make_new_switch(int number_of_ports, int switch_number)
{
    
    pid_t p;
    p = fork();

    string name = "switch " + to_string(switch_number);
    char* pipe = &name[0];
    if (p<0)
    {
        fprintf(stderr, "fork Failed" );
        return;
    }
    else if (p > 0)
    {
        mkfifo(pipe, 0666);
    }
    else
    {
        Switch s(number_of_ports, switch_number, pipe);
        s.switch_handler();
    }
}

void Handler::make_new_system(int system_number)
{
    
    pid_t p;
    p = fork();

    string name = "system " + to_string(system_number);
    char* pipe = &name[0];

    if (p<0)
    {
        fprintf(stderr, "fork Failed" );
        return;
    }
    else if (p > 0)
    {
        mkfifo(pipe, 0666);
    }
    else
    {
        System s(system_number, name);
        s.system_handler();
    }
}

void Handler::connect_system_to_switch(string connect, int system_number, int switch_number)
{
    const char *pchar = connect.c_str();
    char inp[100];
    strcpy(inp, pchar);

    int flag=0;
    for (map<int, int>::iterator it = system_switches.begin(); it != system_switches.end(); ++it)
        if (it->first == system_number)
        {
            flag = 1;
            break;
        }
    if (flag==0)
        system_switches.insert({system_number,switch_number});

    string name = "switch " + to_string(switch_number);
    char* pipe = &name[0];
    int fd = open(pipe, O_WRONLY);
    write(fd,inp,strlen(inp));
    close(fd);

    string name_1 = "system " + to_string(switch_number);
    char* pipe_1 = &name_1[0];
    int fd_1 = open(pipe_1, O_WRONLY);
    write(fd_1,inp,strlen(inp));
    close(fd_1);

    return;
}
