#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[])
{
    struct tms tmsbuf;
    char source_filename[32] = "m2c10_source.txt";
    char destination_filename[32] = "m2c10_destination.txt";

    if (argc != 4)
    {
        printf("usage: %s file_copy_method buffer_size iteration_count\n", argv[0]);
        exit(1);
    }

    int buffer_size = atoi(argv[2]);
    int iteration_count = atoi(argv[3]);
    char *buffer = malloc(buffer_size);

    printf("Clock ticks: %ld\n", sysconf(_SC_CLK_TCK));
    printf("Clocks per second: %ld\n", CLOCKS_PER_SEC);
    printf("\n");

    if (strcmp(argv[1], "raw") == 0)
    {
        int source_fd, destination_fd;
        // Open source file with read-only access
        if ((source_fd = open(source_filename, O_RDONLY)) < 0)
        {
            perror("Error opening source file");
            exit(1);
        }

        // Open destination file with write-only access. Create the file if it
        // doesn't exist.
        if ((destination_fd = open(destination_filename, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG)) < 0)
        {
            perror("Error opening destination file");
            exit(1);
        }
        printf("Raw performance measurement\n");
        printf("===========================\n");
        for (int i = 0; i < iteration_count; i++)
        {
            while ((read(source_fd, buffer, buffer_size)) > 0)
            {
                write(destination_fd, buffer, buffer_size);
            }
        }
        close(source_fd);
        close(destination_fd);
        if (remove(destination_filename) != 0)
        {
            printf("Encountered error while deleting file %s", destination_filename);
        }
    }
    else if (strcmp(argv[1], "stream") == 0)
    {
        FILE *source_fp, *destination_fp;
        // Open source file with read-only access
        if ((source_fp = fopen(source_filename, "r")) == NULL)
        {
            perror("Error opening source file");
            exit(1);
        }

        // Open destination file with write-only access. Create the file if it
        // doesn't exist.
        if ((destination_fp = fopen(destination_filename, "w")) == NULL)
        {
            perror("error opening destination file");
            exit(1);
        }
        printf("Stream performance measurement\n");
        printf("==============================\n");
        for (int i = 0; i < iteration_count; i++)
        {
            while ((fread(buffer, 1, buffer_size, source_fp)) > 0)
            {
                fwrite(buffer, 1, buffer_size, destination_fp);
            }
        }
        fclose(source_fp);
        fclose(destination_fp);
        if (remove(destination_filename) != 0)
        {
            printf("Encountered error while deleting file %s", destination_filename);
        }
    }
    else
    {
        printf("file_copy_method argument must be raw or stream - %s is not valid.\n", argv[1]);
        exit(1);
    }

    times(&tmsbuf);
    printf("User Time        = %.2lf seconds\n", (double)tmsbuf.tms_utime / sysconf(_SC_CLK_TCK));
    printf("System Time      = %.2lf seconds\n", (double)tmsbuf.tms_stime / sysconf(_SC_CLK_TCK));
    printf("Total Clock time = %.2lf seconds\n", (double)clock() / (double)CLOCKS_PER_SEC);
    printf("\n");
}
