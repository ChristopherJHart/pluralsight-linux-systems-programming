#include <limits.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define INPUT_BUFFER_SIZE 4096
#define INPUT_DELIMITERS " \r\n"

char *construct_prompt(char *prompt)
{
    char *cwd[2048];
    char hostname[256];

    // First, get username.
    struct passwd *user = getpwuid(getuid());

    // Next, get hostname of system.
    gethostname(hostname, sizeof(hostname));

    // Next, get user's home directory from environment.
    *cwd = getenv("HOME");

    // If home filepath is not defined, use current working directory.
    if (cwd == NULL)
    {
        getcwd(*cwd, sizeof(cwd));
    }
    // Set current working directory.
    chdir(*cwd);

    // Construct prompt string for shell, then return
    sprintf(prompt, "%s@%s (%s)$ ",
            user->pw_name, hostname, *cwd);
    return prompt;
}

char *read_line_from_input()
{
    char *input;
    size_t buffer_size;

    // getline() will block until input is received from the user.
    if (getline(&input, &buffer_size, stdin) >= 0)
    {
        // If valid input is received from the user, return that input.
        return input;
    }
    // If an EOF is received from the stdin stream, that indicates the user
    // signaled the process should end via Control+D or other such mechanism.
    // Therefore, we should exit.
    else if (feof(stdin))
    {
        exit(0);
    }
    // If a negative integer is returned by getline(), that indicates an error
    // was encountered while reading from the stdin stream. Print the error and
    // exit the shell accordingly.
    else
    {
        perror("Error while reading input");
        exit(1);
    }
}

char **split_input(char *input)
{
    // Array of pointers. Each element represents a string/token.
    char **tokens = malloc(INPUT_BUFFER_SIZE * sizeof(char *));
    // Position within the tokens array
    int token_position = 0;
    // Pointer representing a string/token.
    char *token;

    // This call of strtok() gives us the first token in our user's input.
    token = strtok(input, INPUT_DELIMITERS);
    while (token != NULL)
    {
        // The token in question is placed within our array of pointers
        // (tokens). Our position in the tokens array/buffer is advanced
        // forward by one.
        tokens[token_position] = token;
        token_position++;

        // Pull the next token from the user's input using strtok(). The first
        // argument of NULL is expected, as strtok() internally holds the input
        // string we originally passed in.
        token = strtok(NULL, INPUT_DELIMITERS);
    }
    // Return the array of pointers.
    return tokens;
}

int main()
{
    char prompt_input[INPUT_BUFFER_SIZE];
    char prompt[PATH_MAX];

    // Construct prompt for shell.
    construct_prompt(prompt);

    // This while statement:
    //   1) Prints the prompt to the stdout stream.
    //   2) Reads a new line from the stdin stream, copying it into the
    //      prompt_input variable.
    //   3) Validates that the new line read from the stdin stream is not NULL.
    //      If so, the program breaks out of the loop.
    while (
        fputs(prompt, stdout),
        strcpy(prompt_input, read_line_from_input()),
        prompt_input != NULL)
    {
        // First, split the user's input into an array of
        // strings using our globally-defined delimiters.
        char **argv = split_input(prompt_input);

        // Next, create a new child process.
        pid_t pid = fork();
        if (pid < 0)
        {
            perror("Failed to fork process");
        }
        if (pid == 0)
        {
            // Child process. Call execvp() against the program defined by the
            // user.
            execvp(argv[0], argv);

            // execvp() will perpetually block until the child process
            // terminates. This section of code will not run unless execvp()
            // fails, likely due to the user providing an invalid program name.
            // In this scenario, we should report this error to the user.
            printf("%s: program not found\n", prompt_input);
        }
        else
        {
            // Parent process. Wait for child process to finish before
            // returning prompt by moving to the next iteration of the while
            // loop.
            int child_status = 0;
            waitpid(pid, &child_status, 0);
        }
    }
}
