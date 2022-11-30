#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int timeout = 15;

void timeout_handler() {}

int main()
{
    char username[256] = "";
    char password[256] = "";
    struct sigaction action;

    action.sa_handler = timeout_handler;
    sigemptyset(&action.sa_mask);
    sigaction(SIGALRM, &action, NULL);

    // Read username
    fputs("Enter username: ", stdout);
    fflush(stdout);
    read(0, username, 256);

    // User entered username - display password prompt and start timer.
    fputs("Password: ", stdout);
    fflush(stdout);
    alarm(timeout);
    read(0, password, 256);
    alarm(0);
    if (strlen(password) > 0)
    {
        printf("Thank you for authenticating!\n");
    }
    else
    {
        printf("Timeout while waiting for password!\n");
    }
}
