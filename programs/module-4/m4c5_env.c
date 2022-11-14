#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int c;
    int get_env_var = 0;
    int set_env_var = 0;
    int remove_env_var = 0;
    int index;

    while ((c = getopt(argc, argv, "gsr")) != -1)
    {
        switch (c)
        {
        case 'g':
            get_env_var = 1;
            break;
        case 's':
            set_env_var = 1;
            break;
        case 'r':
            remove_env_var = 1;
            break;
        case '?':
            printf("Usage:\n");
            printf("\t   Get environment variable: %s -g ENV_VAR_NAME\n", argv[0]);
            printf("\t   Set environment variable: %s -s ENV_VAR_NAME value\n", argv[0]);
            printf("\tRemove environment variable: %s -r ENV_VAR_NAME\n", argv[0]);
            exit(1);
        }
    }

    int options = (get_env_var + set_env_var + remove_env_var);

    // Handle scenario where no options are set
    if (options == 0)
    {
        printf("No options were set. Please set one and only one option.\n");
        printf("Usage:\n");
        printf("\t   Get environment variable: %s -g ENV_VAR_NAME\n", argv[0]);
        printf("\t   Set environment variable: %s -s ENV_VAR_NAME value\n", argv[0]);
        printf("\tRemove environment variable: %s -r ENV_VAR_NAME\n", argv[0]);
        exit(1);
    }
    else if (options > 1)
    {
        printf("Multiple options were set. Please set one and only one option.\n");
        printf("Usage:\n");
        printf("\t   Get environment variable: %s -g ENV_VAR_NAME\n", argv[0]);
        printf("\t   Set environment variable: %s -s ENV_VAR_NAME value\n", argv[0]);
        printf("\tRemove environment variable: %s -r ENV_VAR_NAME\n", argv[0]);
        exit(1);
    }

    if (get_env_var == 1)
    {
        char *value;
        for (index = optind; index < argc; index++)
        {
            value = getenv(argv[index]);
            if ((value != NULL))
            {
                printf("Environment variable %s value: %s\n", argv[index], value);
            }
            else
            {
                printf("Environment variable %s not defined.\n", argv[index]);
            }
        }
    }
    else if (set_env_var == 1)
    {
        int ret;
        for (index = optind; index < argc; index += 2)
        {
            // Validate that a value accompanies environment variable name
            if ((index + 1) == argc)
            {
                printf("Environment variable %s was not accompanied by a value.\n", argv[index]);
                exit(1);
            }

            ret = setenv(argv[index], argv[index + 1], 1);
            if (ret == 0)
            {
                printf("Environment variable %s set to value %s\n", argv[index], argv[index + 1]);
            }
            else
            {
                printf(
                    "Could not set environment variable %s to value %s\n",
                    argv[index], argv[index + 1]);
                exit(1);
            }
        }
    }
    else if (remove_env_var == 1)
    {
        int ret;
        for (index = optind; index < argc; index++)
        {
            ret = unsetenv(argv[index]);
            if (ret == 0)
            {
                printf("Environment variable %s has been un-set.\n", argv[index]);
            }
            else
            {
                printf(
                    "Could not un-set environment variable %s\n",
                    argv[index]);
                exit(1);
            }
        }
    }
}
