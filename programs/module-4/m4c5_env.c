#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *value;
    if (argc == 2)
    {
        value = getenv(argv[1]);
        if ((value != NULL))
        {
            printf("Environment variable %s value: %s\n", argv[1], value);
        }
        else
        {
            printf("Environment variable %s not defined.\n", argv[1]);
        }
    }
    else if (argc == 1)
    {
        // Bail out if no argument is provided.
        printf(
            "An environment variable name was not provided. Please provide a "
            "single environment variable to fetch.\n");
        exit(1);
    }
    else
    {
        // Bail out if more than one argument is provided.
        printf(
            "More than two arguments provided. Please provide a single "
            "environment variable to fetch.\n");
        exit(1);
    }
}
