#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define FILENAME "foo.txt"
#define NEW_USER_ID 1001
#define NEW_GROUP_ID 1002

void print_file_owners()
{
    struct stat *file_metadata = malloc(sizeof(struct stat));

    if ((stat(FILENAME, file_metadata)) < 0)
    {
        perror("Failed to retrieve metadata for file");
        exit(1);
    }

    struct passwd *user_data = getpwuid(file_metadata->st_uid);
    if (user_data == NULL)
    {
        perror("Could not find file user owner ID in user database");
        exit(1);
    }

    struct group *group_data = getgrgid(file_metadata->st_gid);
    if (group_data == NULL)
    {
        perror("Could not find file group owner ID in group database");
        exit(1);
    }

    printf("File user owner:  %d (%s)\n", file_metadata->st_uid, user_data->pw_name);
    printf("File group owner: %d (%s)\n", file_metadata->st_gid, group_data->gr_name);
    printf("\n");
}

int main()
{
    mode_t desired_permissions = (S_IRWXU | S_IRWXG | S_IROTH); // 0774

    // Validate we're running with root effective UID/GID.
    if ((geteuid() != 0) || (getegid() != 0))
    {
        perror("Program is not running with root privileges");
        exit(1);
    }

    // Swap to real UID/GID while creating file.
    if (seteuid(getuid()) != 0)
    {
        perror("Failed to de-escalate user privileges");
        exit(1);
    }
    if (setegid(getgid()) != 0)
    {
        perror("Failed to de-escalate group privileges");
        exit(1);
    }

    // Create new file and print its file permissions post-creation.
    printf("Creating new file.\n");
    if (open(FILENAME, O_CREAT, desired_permissions) < 0)
    {
        perror("Failed to open file");
        exit(1);
    }
    print_file_owners();

    // Escalate privileges so we can change user/group owners
    if (seteuid(0) != 0)
    {
        perror("Failed to escalate user privileges");
        exit(1);
    }
    if (setegid(0) != 0)
    {
        perror("Failed to escalate group privileges");
        exit(1);
    }

    // Change file's user owner
    printf("Changing file's user owner.\n");
    if (chown(FILENAME, NEW_USER_ID, -1) < 0)
    {
        perror("Error encountered while changing file's user owner");
        exit(1);
    }
    print_file_owners();

    // Change file's group owner
    printf("Changing file's group owner.\n");
    if (chown(FILENAME, -1, NEW_GROUP_ID) < 0)
    {
        perror("Error encountered while changing file's group owner");
        exit(1);
    }
    print_file_owners();

    // Clean up and remove file.
    if (remove(FILENAME) < 0)
    {
        perror("Failed to delete file");
        exit(1);
    }
}
