#include "handler.h"

int main()
{
    Handler handler;
    while (true)
    {
        handler.get_input();
        handler.input_handler();
    }
}