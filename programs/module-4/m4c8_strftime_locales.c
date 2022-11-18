#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXIMUM_BUFFER_SIZE 4096

void print_time(char *template, struct tm *now)
{
    // Add 1 to buffer size to make room for null terminating character
    int buffer_size = (strftime(NULL, MAXIMUM_BUFFER_SIZE, template, now) + 1);

    // If strftime()'s needed buffer size exceeds our statically-defined
    // maximum capability, return an error and exit.
    if (buffer_size > MAXIMUM_BUFFER_SIZE)
    {
        printf("Large buffer size detected for strftime()\n");
        exit(1);
    }

    // Otherwise, construct a buffer and pass it into strftime(), then print
    // the contents of the buffer.
    char time_str[buffer_size];
    if (strftime(time_str, buffer_size, template, now) > 0)
    {
        printf("%s\n", time_str);
    }
    else
    {
        printf("Error while building time string in strftime()\n");
        exit(1);
    }
}

int main()
{
    struct tm *now_tm;

    // Set locale to use environment variables
    setlocale(LC_ALL, "");

    // Get current locale and print it
    char *current_locale;
    current_locale = setlocale(LC_ALL, NULL);
    printf("Current locale: %s\n", current_locale);

    time_t now = time(NULL);
    now_tm = localtime(&now);

    print_time("%d/%m/%Y", now_tm);
    print_time("%d/%m/%Y %H:%M:%S", now_tm);
    print_time("%-d/%-m/%Y %-H:%-M:%-S", now_tm);
    print_time("%a, %b %m, %Y at %H:%M:%S %Z (%z)", now_tm);
    print_time("%A, %B %m, %Y at %H:%M:%S %Z (%z)", now_tm);
    print_time("%A, %B %m, %Y at %I:%M:%S %p %Z (%z)", now_tm);
}
