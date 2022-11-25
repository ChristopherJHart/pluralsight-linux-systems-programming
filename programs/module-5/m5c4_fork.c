#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t parent_pid = getpid();
    printf("[PID %d] Initializing process.\n", parent_pid);
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("Error encountered while forking new process");
        exit(1);
    }
    else if (pid == 0)
    {
        pid_t child_pid = getpid();
        printf("[PID %d] I am the child process.\n", child_pid);
    }
    else
    {
        printf(
            "[PID %d] I am the parent process that created child "
            "process %d.\n",
            parent_pid, pid);
    }
}
