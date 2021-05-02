#include "switch.h"

Switch::Switch(int number_of_ports, int switch_number)
{
    number_of_ports = number_of_ports;
    switch_number = switch_number;
    for (int i=0; i<number_of_ports; i++)
    {
        string name = "switch " + to_string(switch_number) + " " + to_string(i+1);
        char* pipe = &name[0];
        pipes.push_back(pipe);
        mkfifo(pipe, 0666);
    }
    // cout << "hi\n";
    // cout << pipes[0] << pipes[1];
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

void Switch::switch_handler()
{
    char input[100];
    fd_set fds;
    int maxfd = -1;
    int res;

    for (int i = 0; i < pipes.size(); i++) 
	{ 	
        // cout << i <<pipes[0] << "   " << pipes[1] <<endl;
        int fd_temp = open(pipes[i], O_RDONLY, O_NONBLOCK);
        fd.push_back(fd_temp);
        cout << fd[i];
	}

    while (true)
    {
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
            if (res = FD_ISSET(fd[i], &fds))
            {
                if (read(fd[i], input, sizeof(input))>0)
                {          
                    string command(input);

                    vector <string> tokens;
                    stringstream check1(command); 
                    string intermediate;

                    while(getline(check1, intermediate, ' '))
                        tokens.push_back(intermediate); 

                    if (tokens[0].compare("Connect") == 0)
                        connect(stoi(tokens[1]), stoi(tokens[2]));

                    memset(input, 0, sizeof(input));
                }
            }
            
        }
    }

    for (int i = 0; i < pipes.size(); i++) 
	{ 	
        close(fd[i]);
	}
    
}