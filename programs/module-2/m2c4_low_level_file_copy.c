// include fctnl for open()
#include <fcntl.h>
// include unistd for read(), write(), close()
#include <unistd.h>
// include stdio for printf()
#include <stdio.h>
// include stdlib for exit()
#include <stdlib.h>

#define BUFFER_SIZE 4096

int main()
{
    // File descriptor handlers.
    int source_fd, destination_fd;
    // Source filename to copy from and destination filename to copy to
    char source_filename[32] = "m2c4_source.txt";
    char destination_filename[32] = "m2c4_destination.txt";
    char buffer[BUFFER_SIZE]; // Memory buffer to read/write from/to
    int iterations = 0;       // Counter for number of read/write cycles
    // Counters for amount of data read/written from/to files
    int total_bytes_read = 0;
    int total_bytes_written = 0;
    int bytes_read = 0;
    int bytes_written = 0;

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
    while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0)
    {
        iterations++;
        total_bytes_read += bytes_read;
        bytes_written = write(destination_fd, buffer, bytes_read);
        total_bytes_written += bytes_written;
        printf(
            "[%d] Read %d bytes from %s and wrote %d bytes to %s\n",
            iterations,
            bytes_read,
            source_filename,
            bytes_written,
            destination_filename);
    }
    printf(
        "Read %d total bytes from %s and wrote %d total bytes to %s over %d "
        "iterations\n",
        total_bytes_read,
        source_filename,
        total_bytes_written,
        destination_filename,
        iterations);

    close(source_fd);
    close(destination_fd);
}
