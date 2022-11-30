#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int debug = 0;

void toggle_debugging()
{
    debug ^= 1;
}

int main()
{
    ulong a = 0;
    ulong b = 1;
    ulong c;
    signal(SIGUSR1, toggle_debugging);
    while (1)
    {
        // Crunch some numbers!
        c = a + b;
        a = b;
        b = c;
        if (debug)
        {
            printf("a=%ld, b=%ld\n", a, b);
        }
        sleep(1);
    }
}
