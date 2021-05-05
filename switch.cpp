#include "switch.h"

Switch::Switch(int number_of_ports, int switch_number, string named_pipe)
{
    siginterrupt(SIGALRM, 1);
    number_of_ports = number_of_ports;
    switch_number = switch_number;
    pipe = named_pipe;
    for (int i=0; i<number_of_ports; i++)
    {
        string name = "switch " + to_string(switch_number)+ " " + to_string(i+1);
        char* pipe = &name[0];
        pipes.push_back(name);
        mkfifo(pipe, 0666);
    }
    cout << "Switch " << switch_number <<" created successfully"<<endl;
}

void Switch::connect(int system_number, int port_number)
{
    lookup_table.insert({system_number,port_number});
    file_d.insert({port_number,pipes[port_number-1]});
    cout << pipes[port_number-1]<<endl;
    cout << "switch: system connected to switch!\n";
    return;
}

void Switch::broadcast(char* data)
{
    for (map<int, int>::iterator it = lookup_table.begin(); it != lookup_table.end(); ++it)
    {
        string port_pipe_name = file_d[lookup_table[it->first]];
        char* port_pipe = &port_pipe_name[0];
        int fd = open(port_pipe, O_WRONLY);
        write(fd, data, strlen(data));
        close(fd);
    }
}

void Switch::send(int system_number_1, int system_number_2)
{
    
    char input[100];
    memset(input, 0, sizeof(input));
    string port_pipe_name = file_d[lookup_table[system_number_1]];
    cout << port_pipe_name  << " send "<< endl;
    char* port_pipe = &port_pipe_name[0];
    int fd = open(port_pipe,O_RDONLY ,O_NONBLOCK);
    cout << "FD " << fd << endl;
    if (fd>=0)
    {
        if (read(fd, input, sizeof(input))>0)
        {
            cout << input << "    to switch" << endl;
            memset(input, 0, sizeof(input));
        }
    }
    close (fd);

    int flag = 0;

    for (map<int, int>::iterator it = lookup_table.begin(); it != lookup_table.end(); ++it)
    {
        if (it->first == system_number_2)
        {
            string port_name = file_d[lookup_table[it->first]];
            char* port_pipe = &port_name[0];
            int fd = open(port_pipe, O_WRONLY, O_NONBLOCK);
            cout << "sys FD " << fd  << "   " << port_name<< endl;
            write(fd, input, strlen(input));
            close(fd);
            flag = 1;
            
            break;
        }
    }
    
    cout << flag << endl;
    cout << "data sent!"<<endl;
    if (flag == 0)
        broadcast(input);

    return;
}

void Switch::recieve(int system_number_1, int system_number_2)
{
    string d = "Send " + to_string(system_number_2) + " " + to_string(system_number_1);
    char* inp = &d[0]; 
    for (map<int, int>::iterator it = lookup_table.begin(); it != lookup_table.end(); ++it)
    {
        if (it->first == system_number_2)
        {
            string port_pipe_name = file_d[lookup_table[it->first]];
            char* port_pipe = &port_pipe_name[0];
            int fd = open(port_pipe, O_WRONLY);
            write(fd, inp, strlen(inp));
            close(fd);
            break;
        }
    }
    send(system_number_2, system_number_1);
}

void Switch::listen_to_parrent()
{
    char input[100];
    memset(input, 0, sizeof(input));
    int fd = open(&pipe[0],O_RDONLY, O_NONBLOCK);
    
    if (fd>=0)
    {
        // wait(NULL);
        if (read(fd, input, sizeof(input))>0)
        {   
            string command(input);
            vector <string> tokens;
            stringstream check1(command); 
            string intermediate;

            while(getline(check1, intermediate, ' '))
                tokens.push_back(intermediate); 

            if (tokens[0].compare("Connect") == 0)
                connect(stoi(tokens[1]), stoi(tokens[2]));

            else if (tokens[0].compare("Send") == 0)
                send(stoi(tokens[1]), stoi(tokens[2]));

            // else if (tokens[0].compare("Recieve") == 0)
            //     recieve(stoi(tokens[1]), stoi(tokens[2]));

            memset(input, 0, sizeof(input));
        }
    }
    close (fd);
}

void Switch::switch_handler()
{

    while(true)
    {
        listen_to_parrent();
    }
}

int main(int argc, char** argv)
{
    string s(argv[0]);
    vector <string> tokens;
    stringstream check1(s); 
    string intermediate;

    while(getline(check1, intermediate, ' '))
        tokens.push_back(intermediate); 

    string pipe = "switch " + to_string(stoi(tokens[1]));

    Switch sw(stoi(tokens[0]), stoi(tokens[1]), pipe);
    sw.switch_handler();
}