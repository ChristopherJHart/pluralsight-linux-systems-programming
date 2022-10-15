// include stdio for fopen(), fread(), fwrite(), fclose(),
#include <stdio.h>
// include stdlib for exit()
#include <stdlib.h>

#define BUFFER_SIZE 4096

int main()
{
    FILE *source_fp, *destination_fp;
    char source_filename[32] = "m2c9_source.txt";
    char destination_filename[32] = "m2c9_destination.txt";
    char buffer[BUFFER_SIZE]; // Memory buffer to read/write from/to
    int iterations = 0;       // Counter for number of read/write cycles
    // Counters for amount of data read/written from/to files
    int total_bytes_read = 0;
    int total_bytes_written = 0;
    int bytes_read = 0;
    int bytes_written = 0;

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

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, source_fp)) > 0)
    {
        iterations++;
        total_bytes_read += bytes_read;
        bytes_written = fwrite(buffer, 1, bytes_read, destination_fp);
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

    fclose(source_fp);
    fclose(destination_fp);
}
