#include "system.h"

System::System(int system_number, string my_pipe)
{
    system_number = system_number;
    pipe = &my_pipe[0];
    port;
}

void System::connect(int s_number, int p_number)
{
    switch_number = s_number;
    port = p_number;
    return;
}
void System::send()
{
    string d = "data data data abroo kamooni data";
    char* data = &d[0];
    string temp = "switch " + to_string(switch_number) + " " + to_string(port);
    char* p = &temp[0];
    cout << temp << endl;
    // int fd = open(port, O_WRONLY);
    // write(fd,data,strlen(data));
    // close(fd);
    return;
}
void System::recieve(string data)
{
    return;
}

void System::system_handler()
{
    while (true)
    {
        char input[100];
        memset(input, 0, sizeof(input));
        int fd = open(pipe, O_NONBLOCK);
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

                if (tokens[0].compare("Connect") == 0)
                    connect(stoi(tokens[2]), stoi(tokens[2]));

                else if (tokens[0].compare("Send") == 0)
                    send();

                // else if (tokens[0].compare("Recieve") == 0)
                //     recieve(stoi(tokens[1]), stoi(tokens[2]));

                memset(input, 0, sizeof(input));
            }
        }
        close (fd);
    }
}