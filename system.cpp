#include "system.h"

System::System(int system_number, string my_pipe)
{
    system_number = system_number;
    pipe = &my_pipe[0];
    port;
}

void sig_handler(int signum)
{
    return;
}

void System::connect(int s_number, int p_number)
{
    switch_number = s_number;
    port = p_number;
    cout << "system: system connected to switch!\n";
    return;
}

void System::send()
{
    cout << "hello send system\n";
    // string d = "data data data abroo kamooni data";
    // char* data = &d[0];
    // string temp = "switch " + to_string(switch_number) + " " + to_string(port);
    // char* p = &temp[0];
    // cout << temp << endl;
    // int fd = open(p, O_WRONLY);
    // write(fd,data,strlen(data));
    // close(fd);
    // return;
}

// void System::recieve()
// {
//     char input[100];
//     memset(input, 0, sizeof(input));
//     string temp = "switch " + to_string(switch_number) + " " + to_string(port);
//     char* p = &temp[0];
//     int fd = open(p, O_NONBLOCK);
//     if (fd>=0)
//     {
//         wait(NULL);
//         read(fd, input, sizeof(input));
//         cout << input << "    from other system!" << endl;
//         memset(input, 0, sizeof(input));
//     }
//     close (fd);
//     return;
// }

void System::get_command()
{
    char input[100];
        memset(input, 0, sizeof(input));
        int fd = open(pipe, O_NONBLOCK);
        if (fd>=0)
        {
            // signal(SIGALRM,sig_handler);
            // alarm(TIMEOUT);
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
                //     recieve();

                memset(input, 0, sizeof(input));
            }
        }
        close (fd);
}

// void System::recieve_data()
// {
//     char input[100];
//     memset(input, 0, sizeof(input));
//     string temp = "switch " + to_string(switch_number) + " " + to_string(port);
//     char* p = &temp[0];
//     int fd = open(p, O_NONBLOCK);
//     if (fd>=0)
//     {
//         if (read(fd, input, sizeof(input))>0)
//         {
//             cout << input << "    from other system or switch!" << endl;

//             string command(input);
//             vector <string> tokens;
//             stringstream check1(command); 
//             string intermediate;
//             while(getline(check1, intermediate, ' '))
//                 tokens.push_back(intermediate); 
//             if (tokens[0].compare("Send") == 0)
//                 send();

//             memset(input, 0, sizeof(input));
//         }
//     }
//     close (fd);
//     return;
// }

void System::system_handler()
{
    while (true)
    {
        get_command();
        // recieve_data();
    }
}

int main(int argc, char** argv)
{
    string s(argv[0]);
    string pipe = "system " + to_string(stoi(s));

    System sy(stoi(s), pipe);
    sy.system_handler();
}