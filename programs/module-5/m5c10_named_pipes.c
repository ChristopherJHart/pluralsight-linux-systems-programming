#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 16348
#define INPUT_DELIMITERS " \r\n"

int main()
{
    FILE *pipe_fp, *source_fp;
    char buffer[BUFFER_SIZE];
    int ret;

    // Create named pipe that will transfer data between parent and child
    // process.
    errno = 0;
    ret = mkfifo("m5c10_pipe", S_IRWXU | S_IRWXG);
    // If named pipe already exists, that's fine - ignore that error.
    // Otherwise, return error to the user and exit.
    if (ret < 0 && errno != EEXIST)
    {
        perror("Error while creating named pipe");
        exit(1);
    }

    pid_t pid = fork();
    if (pid > 0)
    {
        // Parent process will read data from source file and write it to the
        // named pipe.

        // First, open named pipe file for writing.
        pipe_fp = fopen("m5c10_pipe", "w");
        if (pipe_fp == NULL)
        {
            perror("Failed to open named pipe for writing in parent process");
            exit(1);
        }

        // Next, open source file for reading.
        source_fp = fopen("m5c10_source.txt", "r");
        if (source_fp == NULL)
        {
            perror("Failed to open source file for reading in parent process");
            exit(1);
        }

        // Finally, continuously push data from source file into named pipe
        // file.
        while ((fread(buffer, BUFFER_SIZE, 1, source_fp) > 0))
        {
            fwrite(buffer, BUFFER_SIZE, 1, pipe_fp);
        }

        fclose(source_fp);
        fclose(pipe_fp);

        int child_status = 0;
        waitpid(pid, &child_status, 0);
        if (child_status > 0)
        {
            perror("Error occurred while processing input in child process\n");
            exit(1);
        }
    }
    else if (pid == 0)
    {
        // Child process will read data from named pipe and identify the
        // longest word used.
        char *longest_word = malloc(sizeof(char *));
        size_t longest_length = 0;
        char *token;

        // Next, open named pipe file for reading.
        pipe_fp = fopen("m5c10_pipe", "r");
        if (pipe_fp == NULL)
        {
            perror("Failed to open named pipe for reading in child process");
            exit(1);
        }

        // Continuously read named pipe file contents into a buffer.
        while ((fread(buffer, BUFFER_SIZE, 1, pipe_fp) > 0))
        {
            // Pull each individual word from the buffer.
            token = strtok(buffer, INPUT_DELIMITERS);
            while (token != NULL)
            {
                // Check to see if the length of the new word is greater than
                // the longest word currently encountered.
                size_t new_length = strlen(token);
                if (new_length > longest_length)
                {
                    // Replace the previous longest word with the current
                    // token and set new longest length.
                    strcpy(longest_word, token);
                    longest_length = new_length;
                    printf("Found new longest word: %s (%ld)\n",
                           longest_word, longest_length);
                }

                // Pull the next individual word from the buffer.
                token = strtok(NULL, INPUT_DELIMITERS);
            }
        }
        // Close out the named pipe stream once we're finished with it.
        fclose(pipe_fp);

        printf("The longest word found is '%s' with a length of %ld characters\n", longest_word, longest_length);
    }
    else
    {
        perror("Error while forking child process");
        exit(1);
    }
}
