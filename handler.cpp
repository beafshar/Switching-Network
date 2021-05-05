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

    if(tokens[0].compare("exit") == 0)
    {
        for (int i=0; i<child_pid.size(); i++)
            kill(child_pid[i], SIGKILL);
        exit(1);
    }
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
        child_pid.push_back(p);
        mkfifo(pipe, 0666);
    }
    else
    {
        string argc = "./switch.out";
        char* arg = &argc[0];
        string num = to_string(number_of_ports) + " " + to_string(switch_number);
        char *pchar = &num[0]; 
        char* argv[] = {pchar,NULL};
        execv(arg, argv);
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
        child_pid.push_back(p);
        mkfifo(pipe, 0666);
    }
    else
    {
        string argc = "./system.out";
        char* arg = &argc[0];
        string system_num = to_string(system_number);
        char *pchar = &system_num[0]; 
        char* argv[] = {pchar,NULL};
        execv(arg, argv);
    }
}

void Handler::connect_system_to_switch(string connect, int system_number, int switch_number)
{
    char* inp = &connect[0];

    int flag = 0;
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

    string name_1 = "system " + to_string(system_number);
    char* pipe_1 = &name_1[0]; 
    int fd_1 = open(pipe_1, O_WRONLY);
    write(fd_1,inp,strlen(inp));
    close(fd_1);

    return;
}
