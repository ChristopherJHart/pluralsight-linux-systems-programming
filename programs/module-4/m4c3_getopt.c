#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int a_flag = 0;
    int b_flag = 0;
    char b_argument[128];
    char c_argument[128];
    int index;
    int c;

    while ((c = getopt(argc, argv, "ab:c::")) != -1)
    {
        switch (c)
        {
        case 'a':
            a_flag = 1;
            break;
        case 'b':
            b_flag = 1;
            strcpy(b_argument, optarg);
            break;
        case 'c':
            if (optarg != 0)
            {
                strcpy(c_argument, optarg);
            }
            else
            {
                strcpy(c_argument, "default");
            }
            break;
        case '?':
            printf("Usage: %s [-a] [-b b_argument] [-c c_argument]\n", argv[0]);
            exit(1);
        }
    }

    // Handle -a option
    if (a_flag == 1)
    {
        printf("-a option is set\n");
    }
    else
    {
        printf("-a option is not set\n");
    }

    // Handle -b option
    if (b_flag == 1)
    {
        printf("-b option has an argument of %s\n", b_argument);
    }
    else
    {
        printf("-b option was not provided by command line.\n");
    }

    // Handle -c option
    if (strcmp(c_argument, "") != 0)
    {
        printf("-c option argument is %s\n", c_argument);
    }
    else
    {
        printf("-c option was not provided by command line.\n");
    }

    // Display non-option arguments
    for (index = optind; index < argc; index++)
        printf("Non-option argument %s\n", argv[index]);
}
