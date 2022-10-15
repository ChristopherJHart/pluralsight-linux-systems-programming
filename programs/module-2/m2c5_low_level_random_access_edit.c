#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
// include string for strcpy()
#include <string.h>

struct employee_record
{
    int employee_id;
    char first_name[256];
    char last_name[256];
};

int main(int argc, char *argv[])
{
    int fd;
    int record_size = sizeof(struct employee_record);
    if ((fd = open("employee_database", O_RDWR | O_CREAT, S_IRWXU | S_IRWXG)) < 0)
    {
        perror("Error opening employee database");
        exit(1);
    }
    if (argc == 1)
    {
        struct employee_record e1;
        e1.employee_id = 1;
        strcpy(e1.first_name, "Jimmy");
        strcpy(e1.last_name, "Taylor");

        struct employee_record e2;
        e2.employee_id = 2;
        strcpy(e2.first_name, "Anna");
        strcpy(e2.last_name, "Cooper");

        struct employee_record e3;
        e3.employee_id = 3;
        strcpy(e3.first_name, "Sylvia");
        strcpy(e3.last_name, "Baker");

        int written = 0;
        written += write(fd, &e1, record_size);
        written += write(fd, &e2, record_size);
        written += write(fd, &e3, record_size);

        printf("Wrote %d bytes to employee database.\n", written);
    }
    else if (argc == 2)
    {
        int record_to_fetch = atoi(argv[1]);
        printf("Fetching employee record %d in database...\n", record_to_fetch);
        int seek_location = (record_to_fetch - 1) * record_size;
        lseek(fd, seek_location, SEEK_SET);
        struct employee_record fetched_record;
        int read_bytes = read(fd, &fetched_record, record_size);
        if (read_bytes > 0)
        {
            printf("Employee record\n");
            printf("===============\n");
            printf("Employee ID: %d\n", fetched_record.employee_id);
            printf(" First Name: %s\n", fetched_record.first_name);
            printf("  Last Name: %s\n", fetched_record.last_name);
        }
        else
        {
            printf("Failed to find employee record at %d\n", record_to_fetch);
            exit(1);
        }
        printf("Edit employee record? [y/n]: ");
        char edit_input[256];
        scanf("%s", edit_input);
        if ((strcmp(edit_input, "y")) == 0)
        {
            int record_edited = 0;
            int new_id;
            printf("New employee ID? [%d]: ", fetched_record.employee_id);
            scanf("%d", &new_id);
            if ((new_id != fetched_record.employee_id))
            {
                fetched_record.employee_id = new_id;
                record_edited = 1;
            }

            char new_first_name[256];
            printf("New employee first name? [%s]: ", fetched_record.first_name);
            scanf("%s", new_first_name);
            if ((strcmp(new_first_name, fetched_record.first_name)) != 0)
            {
                strcpy(fetched_record.first_name, new_first_name);
                record_edited = 1;
            }

            char new_last_name[256];
            printf("New employee last name? [%s]: ", fetched_record.last_name);
            scanf("%s", new_last_name);
            if ((strcmp(new_last_name, fetched_record.last_name)) != 0)
            {
                strcpy(fetched_record.last_name, new_last_name);
                record_edited = 1;
            }

            if (record_edited == 1)
            {

                lseek(fd, seek_location, SEEK_SET);
                int bytes_written = write(fd, &fetched_record, record_size);
                printf("Wrote %d bytes to employee database.\n", bytes_written);
            }
        }
    }
    else
    {
        // Bail out if more than one argument is provided.
        printf(
            "More than two arguments provided. Please provide a single "
            "employee record to retrieve.\n");
        exit(1);
    }
    close(fd);
}
