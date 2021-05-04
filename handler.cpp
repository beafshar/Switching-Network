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
    
    if (tokens[0].compare("Connect") == 0){
        connect_system_to_switch(current_input, stoi(tokens[1]), stoi(tokens[2]), stoi(tokens[3]));
    }
        
}

void Handler::make_new_switch(int number_of_ports, int switch_number)
{
    
    pid_t p;
    p = fork();
    int fd[2]; // 0 for read, 1 for write

    if (pipe(fd) < 0 )
    {
            printf("error occured in opening province pipe.\n");
    }

    if (p<0)
    {
        fprintf(stderr, "fork Failed" );
        return;
    }
    else if (p > 0)
    {
        close(fd[0]);
        switches.insert({switch_number, fd[1]});
    }
    else
    {
        close(fd[1]);
        Switch s(number_of_ports, switch_number,fd[0]);
        s.switch_handler();
    }
}

void Handler::make_new_system(int system_number)
{
    pid_t p;
    p = fork();

    int fd[2]; // 0 for read, 1 for write

    if (pipe(fd) < 0 )
    {
            printf("error occured in opening province pipe.\n");
    }
    if (p<0)
    {
        fprintf(stderr, "fork Failed" );
        return;
    }
    else if (p > 0)
    {
        close(fd[0]);
        systems.insert({system_number, fd[1]});
    }
    else
    {
        close(fd[1]);
        System s(system_number, fd[0]);
    }
}

void Handler::connect_system_to_switch(string connect, int system_number, int switch_number, int port_number)
{


    
    const char *pchar = connect.c_str();
    char inp[100];
    strcpy(inp, pchar);

    int switch_fd = switches[switch_number];

    cout << switch_fd << endl;
    write(switch_fd,inp, SIZE);

    cout << connect<<"jjjjjjjj" << endl;

    int system_fd = systems[system_number];
    write(system_fd,inp, SIZE);

    cout << "kkkkkkkkkkkkkkkk"<< endl;

    return;
}