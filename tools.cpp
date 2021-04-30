#include "headers.h"

void input_handler(string input)
{
    vector <string> tokens;
    stringstream check1(input); 
    string intermediate;

    while(getline(check1, intermediate, ' ')) 
    { 
        tokens.push_back(intermediate); 
    }

    if (tokens[0].compare("MySwitch") == 0)
    {
        // fork and make a new switch
    }

    if (tokens[0].compare("‫‪MySystem‬‬") == 0)
    {
        // fork and make a new system
    }
}