#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define FILENAME "foo.txt"

void print_file_permissions()
{
    struct stat *file_metadata = malloc(sizeof(struct stat));
    if ((stat(FILENAME, file_metadata)) < 0)
    {
        perror("Failed to retrieve metadata for file");
        exit(1);
    }
    printf("File permissions: %04o\n", (file_metadata->st_mode & (S_IRWXU | S_IRWXG | S_IRWXO)));
}

int main()
{
    mode_t desired_permissions = (S_IRWXU | S_IRWXG | S_IROTH); // 0774
    mode_t new_umask = (S_IWGRP | S_IWOTH);                     // 0022

    // Change current umask value
    mode_t mask = umask(new_umask);
    printf("Previous umask value: %04o\n", mask);
    printf("     New umask value: %04o\n", new_umask);

    // Create new file and print its file permissions post-creation.
    if (open(FILENAME, O_CREAT, desired_permissions) < 0)
    {
        perror("Failed to open file");
        exit(1);
    }
    print_file_permissions();

    // Explicitly modify file's permissions, ignoring umask value.
    if (chmod(FILENAME, desired_permissions) < 0)
    {
        perror("Failed to modify permissions for file");
        exit(1);
    }
    print_file_permissions();

    // Clean up and remove file.
    if (remove(FILENAME) < 0)
    {
        perror("Failed to delete file");
        exit(1);
    }
}
