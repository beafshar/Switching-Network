#include "switch.h"

Switch::Switch(int number_of_ports, int switch_number, string named_pipe)
{
    siginterrupt(SIGALRM, 1);
    number_of_ports = number_of_ports;
    switch_number = switch_number;
    pipe = named_pipe;
    frame_size = 100;
    for (int i=0; i<number_of_ports; i++)
    {
        string name = "switch " + to_string(switch_number)+ " " + to_string(i+1);
        char* pipe = &name[0];
        pipes.push_back(name);
        mkfifo(pipe, 0666);
    }
    cout << "Switch " << switch_number <<" with " << number_of_ports <<" ports created successfully"<<endl;
}

void Switch::connect(int system_number, int port_number)
{
    lookup_table.insert({system_number,port_number});
    file_d.insert({port_number,pipes[port_number-1]});
    cout << "System " << system_number <<  " connected to switch " << switch_number << " on port " << port_number << endl;
    return;
}

void Switch::connect_to_switch(int snum_1, int pnum_1, int snum_2, int pnum_2)
{
    if (snum_1 == switch_number)
    {
        switch_port.insert({snum_2,pnum_2});
        switch_switch.insert({snum_2,pnum_1});
        cout << "Switch "<< snum_1 << " on port " << pnum_1 <<" connected to switch " << snum_2 << " on port " << pnum_2 << endl;
    }
    else
    {
        switch_port.insert({snum_1,pnum_1});
        switch_switch.insert({snum_1,pnum_2});   
    }
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

    for (map<int, int>::iterator it = switch_switch.begin(); it != switch_switch.end(); ++it)
    {
        string port_pipe_name = "switch " + to_string(it->first) + " " + to_string(switch_port[it->first]);
        char* port_pipe = &port_pipe_name[0];
        int fd = open(port_pipe, O_WRONLY);
        write(fd, data, strlen(data));
        close(fd);
    }

    return;
}

void Switch::send(int system_number_1, int system_number_2)
{
    string d = "";
    int i = 1;
    while(true)
    {
        char input[100];
        memset(input, 0, sizeof(input));
        string port_pipe_name = file_d[lookup_table[system_number_1]];
        char* port_pipe = &port_pipe_name[0];
        int fd = open(port_pipe, O_RDONLY);
        if (fd>=0)
        {
            wait(NULL);
            read(fd, input, sizeof(input));
            cout << "Switch " << switch_number << ": frame " << i <<" recieved\n";
            string s(input);
            vector <string> tokens;
            stringstream check1(s); 
            string intermediate;

            while(getline(check1, intermediate, '#'))
                tokens.push_back(intermediate); 
            d += tokens[0];
            if (tokens.size()==1)
            {
                memset(input, 0, sizeof(input));
                break;
            }
            i++;
            memset(input, 0, sizeof(input));
        }
        close (fd);
    }

    char* data = &d[0];
    int flag = 0;
    for (map<int, int>::iterator it = lookup_table.begin(); it != lookup_table.end(); ++it)
    {
        if (it->first == system_number_2)
        {

            if (sizeof(d) <= frame_size)
    {
        string port_name = file_d[lookup_table[it->first]];
        char* port_pipe = &port_name[0];
        int fd = open(port_pipe, O_WRONLY);
        int t = write(fd,data,strlen(data));
        close(fd);
        cout << "Switch "<< switch_number << ": frame 1 sent\n";
    }
    else
    {
        int i = 1;
        while (sizeof(d)>frame_size)
        {
            string temp_1 = "";
            string temp_2 = "";
            for(int j=0;j<frame_size;j++)
                temp_1 += d[j];
            temp_1 += "#a";
            for(int j=frame_size;j<sizeof(d);j++)
                temp_2 += d[j];
            d = temp_2;

            char* data = &temp_1[0];
            string port_name = file_d[lookup_table[it->first]];
            char* port_pipe = &port_name[0];
            int fd = open(port_pipe, O_WRONLY);
            int t = write(fd,data,strlen(data));
            close(fd);   
            cout << "Switch "<< switch_number << ": frame " << i <<" sent\n";
        }
        
    }
        }
    }
    
    if (flag == 0)
        broadcast(data);

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

    int fd = open(&pipe[0],O_RDONLY);
    
    if (fd>=0)
    {
        if (read(fd, input, sizeof(input))>0)
        {   
            string command(input);
            vector <string> tokens;
            stringstream check1(command); 
            string intermediate;

            while(getline(check1, intermediate, ' '))
                tokens.push_back(intermediate); 

            if (tokens[0].compare("connect_system_to_switch") == 0)
                connect(stoi(tokens[1]), stoi(tokens[2]));

            else if (tokens[0].compare("send_data") == 0)
                send(stoi(tokens[1]), stoi(tokens[2]));

            else if (tokens[0].compare("recieve_data") == 0)
                recieve(stoi(tokens[1]), stoi(tokens[2]));

            else if (tokens[0].compare("connect_switch_to_switch"))
                connect_to_switch(stoi(tokens[0]),stoi(tokens[1]),stoi(tokens[2]),stoi(tokens[3]));

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

    // siginterrupt(SIGALRM, 1);
    Switch sw(stoi(tokens[0]), stoi(tokens[1]), pipe);
    sw.switch_handler();
}