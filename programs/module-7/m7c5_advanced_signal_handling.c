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

    // Build sigaction structure
    struct sigaction action;
    action.sa_handler = sigint_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;

    // Register handler for SIGINT
    sigaction(SIGINT, &action, NULL);

    printf("Starting counter.\n");
    sigset_t block_mask;
    sigaddset(&block_mask, SIGINT);
    while (1)
    {
        COUNTER += 1;
        printf("Counter: %d\n", COUNTER);
        sigprocmask(SIG_BLOCK, &block_mask, NULL);
        sleep(1);
        sigprocmask(SIG_UNBLOCK, &block_mask, NULL);
    }
}
