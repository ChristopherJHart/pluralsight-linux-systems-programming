#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    printf("Starting critical path.\n");
    sigset_t block_mask;
    sigfillset(&block_mask);
    sigdelset(&block_mask, SIGHUP);
    sigprocmask(SIG_BLOCK, &block_mask, NULL);
    while (1)
    {
        printf("I'm in the critical path!\n");
        sleep(1);
    }
    sigprocmask(SIG_UNBLOCK, &block_mask, NULL);
}
