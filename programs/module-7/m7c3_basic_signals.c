#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    while (1)
    {
        pid_t pid = fork();
        if (pid > 0) // Parent process
        {
            printf("Created child process %d\n", pid);
            int child_status;
            waitpid(pid, &child_status, 0);
            if (WIFEXITED(child_status) > 0)
            {
                printf("Child process %d exited normally with an exit status of %d\n",
                       pid, child_status);
            }
            else if (WIFSIGNALED(child_status) > 0)
            {
                if (WCOREDUMP(child_status) > 0)
                {
                    printf("Child process %d exited with a core dump, signal of %d (%s)\n",
                           pid,
                           WTERMSIG(child_status),
                           strsignal(WTERMSIG(child_status)));
                }
                else
                {
                    printf("Child process %d exited with a signal of %d (%s)\n",
                           pid,
                           WTERMSIG(child_status),
                           strsignal(WTERMSIG(child_status)));
                }
            }
        }
        else if (pid == 0) // Child process
        {
            while (1)
            {
                sleep(1);
            }
        }
        else
        {
            perror("Failed to create new child process");
            exit(1);
        }
    }
}
