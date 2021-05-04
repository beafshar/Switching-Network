#include "switch.h"

Switch::Switch(int number_of_ports, int switch_number, int read_fd)
{
    
    number_of_ports = number_of_ports;
    switch_number = switch_number;
    unnamed_pipe = read_fd;
    for (int i=0; i<number_of_ports; i++)
    {
        string name = "switch " + to_string(switch_number) + to_string(i+1);
        char* pipe = &name[0];
        pipes.push_back(name);
        mkfifo(pipe, 0666);
        
    }

}

void Switch::connect(int system_number, int port_number)
{
    lookup_table.insert({port_number,system_number});
    file_d.insert({pipes[port_number-1],port_number});
    return;
}

void Switch::send(int system_number_1, int system_number_2)
{
    return;
}

void Switch::recieve(int system_number_1, int system_number_2)
{
    return;
}

void Switch::listen_to_parrent(fd_set fds)
{
    char input[100];

    FD_ZERO(&fds);
    if (int res = FD_ISSET(unnamed_pipe, &fds))
    {
        if (read(unnamed_pipe, input, sizeof(input))>0)
        {          
            string command(input);

            vector <string> tokens;
            stringstream check1(command); 
            string intermediate;
            cout <<tokens[0]<<endl;

            while(getline(check1, intermediate, ' '))
                tokens.push_back(intermediate); 

            if (tokens[0].compare("Connect") == 0)
                connect(stoi(tokens[1]), stoi(tokens[2]));

            else if (tokens[0].compare("Send") == 0)
                send(stoi(tokens[1]), stoi(tokens[2]));

            else if (tokens[0].compare("Recieve") == 0)
                recieve(stoi(tokens[1]), stoi(tokens[2]));

            memset(input, 0, sizeof(input));
        }
    }

    
}

void Switch::listen_to_fifo(fd_set fds, int maxfd)
{
    
    char input[100];

    FD_ZERO(&fds);

    for (int i = 0; i < fd.size(); i++) 
    { 	
        FD_SET(fd[i] , &fds);
        if(fd[i] > maxfd) 
            maxfd = fd[i];
    }

    select( maxfd + 1 , &fds , NULL , NULL , NULL); 
    for (int i=0; i<fd.size(); i++)
    {
        if (int res = FD_ISSET(fd[i], &fds))
        {
            if (read(fd[i], input, sizeof(input))>0)
            {          
                string command(input);

                vector <string> tokens;
                stringstream check1(command); 
                string intermediate;

                // while(getline(check1, intermediate, ' '))
                //     tokens.push_back(intermediate); 

                // if (tokens[0].compare("Connect") == 0)
                //     connect(stoi(tokens[1]), stoi(tokens[2]));

                memset(input, 0, sizeof(input));
            }
        }
        
    }
}
void Switch::switch_handler()
{

    fd_set fds;
    int maxfd = -1;

    for (int i = 0; i < pipes.size(); i++) 
	{ 	
        cout << i <<pipes[i] << "   " <<" line 45"<<endl;
        int fd_temp = open(&pipes[i][0], O_RDONLY, O_NONBLOCK);
        fd.push_back(fd_temp);
        cout << fd[i];
	}

    while(true){

        listen_to_parrent(fds);
        listen_to_fifo(fds, maxfd);

    }
    


    for (int i = 0; i < pipes.size(); i++) 
	{ 	
        close(fd[i]);
	}
    
}