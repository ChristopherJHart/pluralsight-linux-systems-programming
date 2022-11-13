#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("%d total arguments provided:\n", argc);
    for (int i = 0; i < argc; i++)
    {
        printf("\tArgument %d: %s\n", i, argv[i]);
    }
}
