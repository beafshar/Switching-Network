#include "system.h"

System::System(int system_number, string my_pipe)
{
    system_number = system_number;
    pipe = my_pipe;
    port;
    frame_size = 100;
    cout << "System " << system_number <<" created successfully"<<endl;
}

void sig_handler(int signum)
{
    return;
}

void System::connect(int s_number, int p_number)
{
    switch_number = s_number;
    port = p_number;
    return;
}

void System::send()
{
    string d = "test data for sending";
    if (sizeof(d) <= frame_size)
    {
        char* data = &d[0];
        string temp = "switch " + to_string(switch_number) + " " + to_string(port);
        char* p = &temp[0];
        int fd = open(p, O_WRONLY);
        int t = write(fd,data,strlen(data));
        close(fd);
        cout << "System "<< system_number << ": frame 1 sent\n";
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
            string temp = "switch " + to_string(switch_number) + " " + to_string(port);
            char* p = &temp[0];
            int fd = open(p, O_WRONLY);
            int t = write(fd,data,strlen(data));
            close(fd);   
            cout << "System "<< system_number << ": frame " << i <<" sent\n";
        }
        
    }
    

    return;
}

void System::recieve()
{
    string data = "";
    int i = 1;
    while(true)
    {
        char input[100];
        memset(input, 0, sizeof(input));
        string temp = "switch " + to_string(switch_number) + " " + to_string(port);
        char* p = &temp[0];
        int fd = open(p, O_RDONLY);
        if (fd>=0)
        {
            wait(NULL);
            read(fd, input, sizeof(input));
            cout << "System "<< system_number << ": frame " << i <<" recieved\n";
            string s(input);
            vector <string> tokens;
            stringstream check1(s); 
            string intermediate;

            while(getline(check1, intermediate, '#'))
                tokens.push_back(intermediate); 
            data += tokens[0];
            if (tokens.size()==1)
            {
                cout << "System "<< system_number << ": data: " << data << endl;
                memset(input, 0, sizeof(input));
                break;
            }
            i++;
            memset(input, 0, sizeof(input));
        }
        close (fd);
    }
    
    return;
}

void System::get_command()
{
    char input[100];
    memset(input, 0, sizeof(input));
    
    int fd = open(&pipe[0],O_RDONLY);
    if (fd>=0)
    {
        signal(SIGALRM,sig_handler);
        alarm(TIMEOUT);
        int res = read(fd, input, sizeof(input));
        if (res>0)
        {
            string command(input);
            vector <string> tokens;
            stringstream check1(command); 
            string intermediate;

            while(getline(check1, intermediate, ' '))
                tokens.push_back(intermediate); 

            if (tokens[0].compare("connect_system_to_switch") == 0)
                connect(stoi(tokens[2]), stoi(tokens[3]));

            else if (tokens[0].compare("send_data") == 0)
                send();

            else if (tokens[0].compare("recieve_data") == 0)
                recieve();

            memset(input, 0, sizeof(input));
        }
    }
        close (fd);
}

void System::system_handler()
{
    while (true)
    {
        signal(SIGALRM,sig_handler);
        alarm(TIMEOUT);
        get_command();
        alarm(0);
        recieve();
    }
}

int main(int argc, char** argv)
{
    string s(argv[0]);
    string pipe = "system " + to_string(stoi(s));

    siginterrupt(SIGALRM, 1);
    System sy(stoi(s), pipe);
    sy.system_handler();
}