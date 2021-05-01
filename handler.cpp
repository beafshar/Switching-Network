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
        connect_system_to_switch(stoi(tokens[1]), stoi(tokens[2]), stoi(tokens[3]));
}

void Handler::make_new_switch(int number_of_ports, int switch_number)
{
    int fd[2];
    if (pipe(fd)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return;
    }
    pid_t p;
    p = fork();
    if (p<0)
    {
        fprintf(stderr, "fork Failed" );
        return;
    }
    else if (p > 0)
    {
        vector<int> f;
        f.push_back(fd[0]);
        f.push_back(fd[1]);
        switch_file_discriptors.push_back(f);
        switches.push_back(switch_number);
    }
    else
    {
        Switch s(number_of_ports, switch_number, fd);
    }
}

void Handler::make_new_system(int system_number)
{
    int fd[2];
    if (pipe(fd)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return;
    }
    pid_t p;
    p = fork();
    if (p<0)
    {
        fprintf(stderr, "fork Failed" );
        return;
    }
    else if (p > 0)
    {
        vector<int> f;
        f.push_back(fd[0]);
        f.push_back(fd[1]);
        system_file_discriptors.push_back(f);
        switches.push_back(system_number);
    }
    else
    {
        System s(system_number, fd);
    }
}

void Handler::connect_system_to_switch(int system_number, int switch_number, int port_number)
{
    
}