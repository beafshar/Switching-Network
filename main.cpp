#include "system.h"
#include "switch.h"
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