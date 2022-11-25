#include <unistd.h>

int main()
{
    char *argv;
    int pipe_fd[2];
    pipe(pipe_fd);
    pid_t pid = fork();
    if (pid > 0) // Parent
    {
        dup2(pipe_fd[0], 0);
        close(pipe_fd[1]);
    }
    else if (pid == 0) // Child
    {
        dup2(pipe_fd[1], 1);
        close(pipe_fd[0]);
        execvp("foo", argv);
    }
}
