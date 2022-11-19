#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <time.h>

int main()
{
    struct tms tmsbuf;
    clock_t start, end;
    double cpu_time_used;

    printf("Clock ticks: %ld\n", sysconf(_SC_CLK_TCK));
    printf("Clocks per second: %ld\n", CLOCKS_PER_SEC);
    printf("\n");

    // Write random data to /dev/null
    start = clock();
    int fd = open("/dev/null", O_RDWR);
    for (int i = 0; i < 100000000; i++)
    {
        write(fd, &i, sizeof(i));
    }
    close(fd);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Finished writing data in %f seconds.\n", cpu_time_used);
    printf("\n");

    // Display process time
    times(&tmsbuf);
    printf("User Time        = %.2lf seconds\n", (double)tmsbuf.tms_utime / sysconf(_SC_CLK_TCK));
    printf("System Time      = %.2lf seconds\n", (double)tmsbuf.tms_stime / sysconf(_SC_CLK_TCK));
    printf("\n");
}
