#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// include sys/uio.h for iovec, readv(), writev()
#include <sys/uio.h>

#define NUMBER_OF_BUFFERS 5

struct employee_record
{
    int employee_id;
    char first_name[256];
    char last_name[256];
};

int main(int argc, char **argv)
{
    int fd;
    struct iovec iov[NUMBER_OF_BUFFERS];
    int record_size = sizeof(struct employee_record);
    ssize_t bytes_read = 0;
    ssize_t bytes_written = 0;
    if ((fd = open("employee_database_scatter_gather", O_RDWR | O_CREAT, S_IRWXU | S_IRWXG)) < 0)
    {
        perror("Error opening employee database");
        exit(1);
    }
    // Populate iovec structures with buffers
    for (int i = 0; i < NUMBER_OF_BUFFERS; i++)
    {
        iov[i].iov_base = malloc(record_size);
        iov[i].iov_len = record_size;
    }

    if (argc == 2)
    {
        if (strcmp(argv[1], "fetch") == 0)
        {
            printf("Fetching employee records from database...\n");
            while ((bytes_read = readv(fd, iov, NUMBER_OF_BUFFERS)) > 0)
            {
                printf("Read %ld bytes from employee database:\n", bytes_read);
                for (int i = 0; i < NUMBER_OF_BUFFERS; i++)
                {
                    struct employee_record *record = (struct employee_record *)iov[i].iov_base;
                    printf("(IOV buffer %d) [%d]: %s %s\n",
                           i,
                           record->employee_id,
                           record->first_name,
                           record->last_name);
                }
            }
            if (bytes_read < 0)
            {
                perror("Error while reading from employee database");
                exit(1);
            }
        }
        else if (strcmp(argv[1], "create") == 0)
        {
            struct employee_record records[NUMBER_OF_BUFFERS] =
                {
                    {1, "Jimmy", "Taylor"},
                    {2, "Anna", "Cooper"},
                    {3, "Sylvia", "Baker"},
                    {4, "Helene", "Stern"},
                    {5, "Steven", "Garcia"},
                };
            // Copy structures into iovec buffers
            for (int i = 0; i < NUMBER_OF_BUFFERS; i++)
            {
                memcpy(iov[i].iov_base, &records[i], record_size);
            }

            // Write structures/iovec buffers to file
            bytes_written = writev(fd, iov, NUMBER_OF_BUFFERS);
            printf("Wrote %ld bytes\n", bytes_written);
        }
        else
        {
            printf("Invalid argument %s provided.\n", argv[1]);
        }
    }
    else
    {
        // Bail out if more than one argument is provided.
        printf(
            "More than two arguments provided. Please indicate whether you "
            "want to create employee records, or fetch them.\n");
        exit(1);
    }
    close(fd);
}
