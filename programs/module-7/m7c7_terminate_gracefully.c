#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FILEPATH "/tmp/foo.txt"
#define CONTENT "Test string\n"

void sigterm_handler()
{
    if (unlink(FILEPATH) < 0)
    {
        perror("Failed to delete file");
    }
    else
    {
        printf("Successfully deleted file %s\n", FILEPATH);
    }
    exit(1);
}

int main()
{
    FILE *stream;

    // Register SIGTERM handler
    signal(SIGTERM, sigterm_handler);
    printf("Opening temporary file.\n");
    stream = fopen(FILEPATH, "w");
    if (stream == NULL)
    {
        perror("Failed to open stream");
        exit(1);
    }
    printf("Starting critical path.\n");
    while (1)
    {
        if (fwrite(CONTENT, sizeof(CONTENT), 1, stream) > 0)
        {
            printf("Wrote data to file.\n");
            fflush(stream);
        }
        sleep(1);
    }
}
