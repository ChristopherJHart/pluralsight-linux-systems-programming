#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int COUNTER = 0;

void sigint_handler(int signal)
{
    printf("%s received, reset counter.\n", strsignal(signal));
    COUNTER = 0;
}

int main()
{
    // Register handler for SIGINT
    signal(SIGINT, sigint_handler);

    printf("Starting counter.\n");
    while (1)
    {
        COUNTER += 1;
        printf("Counter: %d\n", COUNTER);
        sleep(1);
    }
}
