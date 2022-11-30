#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CONFIG_FILEPATH "/tmp/config.txt"
#define BUFFER_SIZE 256

int modulus = 0;
int numerator = 0;

void sighup_read_configuration()
{
    FILE *stream;
    char *line;
    size_t len = 256;

    stream = fopen(CONFIG_FILEPATH, "r");
    if (stream == NULL)
    {
        perror("Failed to open stream to configuration file");
        exit(1);
    }
    getline(&line, &len, stream);
    modulus = atoi(line);
    numerator = 0;
    printf("Reconfigured to use modulus of %d\n", modulus);
    fclose(stream);
}

int main()
{
    signal(SIGHUP, sighup_read_configuration);
    raise(SIGHUP);
    while (1)
    {
        if ((numerator % modulus) == 0)
        {
            printf("%d is divisible by %d\n", numerator, modulus);
            sleep(1);
        }
        numerator += 1;
    }
}
