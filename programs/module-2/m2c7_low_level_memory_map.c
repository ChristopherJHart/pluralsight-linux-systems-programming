#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// include sys/mman.h for mmap()
#include <sys/mman.h>

struct employee_record
{
    int employee_id;
    char first_name[256];
    char last_name[256];
};

int main(int argc, char **argv)
{
    int fd;
    size_t database_size;
    struct employee_record *records;
    int record_size = sizeof(struct employee_record);
    if ((fd = open("employee_database_memory_map", O_RDWR | O_CREAT, S_IRWXU | S_IRWXG)) < 0)
    {
        perror("Error opening employee database");
        exit(1);
    }
    if (argc == 2)
    {
        if (strcmp(argv[1], "fetch") == 0)
        {
            printf("Fetching employee records from database...\n");
            database_size = lseek(fd, 0, SEEK_END);
            records = (struct employee_record *)mmap(NULL, database_size,
                                                     PROT_READ,
                                                     MAP_PRIVATE, fd, 0);
            for (int i = 0; i < (int)database_size / record_size; i++)
            {
                struct employee_record record = records[i];
                printf(
                    "[%d]: %s %s\n",
                    record.employee_id,
                    record.first_name,
                    record.last_name);
            }
            if (munmap(records, database_size) < 0)
            {
                perror("Error unmapping memory region");
                exit(1);
            }
        }
        else if (strcmp(argv[1], "create") == 0)
        {
            struct employee_record records[5] =
                {
                    {1, "Jimmy", "Taylor"},
                    {2, "Anna", "Cooper"},
                    {3, "Sylvia", "Baker"},
                    {4, "Helene", "Stern"},
                    {5, "Steven", "Garcia"},
                };

            int written = 0;
            for (int i = 0; i < 5; i++)
            {
                written += write(fd, &records[i], record_size);
            }
            printf("Wrote %d bytes to employee database.\n", written);
        }
        else if (strcmp(argv[1], "nullify") == 0)
        {
            printf("Fetching employee records from database...\n");
            database_size = lseek(fd, 0, SEEK_END);
            records = (struct employee_record *)mmap(NULL, database_size,
                                                     PROT_READ | PROT_WRITE,
                                                     MAP_SHARED, fd, 0);
            for (int i = 0; i < (int)database_size / record_size; i++)
            {

                records[i].employee_id = 99;
                printf("Changed %s %s employee ID to %d\n", records[i].first_name, records[i].last_name, records[i].employee_id);
            }
            if (msync(records, database_size, MS_SYNC) < 0)
            {
                perror("Writing to database failed.");
                exit(1);
            }
            printf("Modified all employee IDs to be 99.\n");
            if (munmap(records, database_size) < 0)
            {
                perror("Error unmapping memory region");
                exit(1);
            }
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
