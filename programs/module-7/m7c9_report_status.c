#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

ulong numbers_crunched = 0;
ulong numbers_crunched_since_last_report = 0;

void report_statistics()
{
    printf(
        "%ld numbers crunched so far, %ld numbers crunched since last report.\n",
        numbers_crunched,
        numbers_crunched_since_last_report);
    numbers_crunched_since_last_report = 0;
}

int main()
{
    ulong a = 0;
    ulong b = 1;
    ulong c;
    signal(SIGUSR1, report_statistics);
    while (1)
    {
        // Crunch some numbers!
        c = a + b;
        a = b;
        b = c;
        numbers_crunched += 1;
        numbers_crunched_since_last_report += 1;
    }
}
