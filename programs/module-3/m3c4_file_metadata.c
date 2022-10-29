#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        int ret;
        struct stat *file_metadata = malloc(sizeof(struct stat));
        if ((ret = stat(argv[1], file_metadata)) < 0)
        {
            perror("Failed to retrieve file metadata for file");
            exit(1);
        }
        printf("File Metadata for %s\n", argv[1]);
        printf("==================");
        for (u_int32_t i = 0; i < strlen(argv[1]); i++)
        {
            printf("=");
        }
        printf("\n");
        // Display file type
        printf("File type: ");
        switch (file_metadata->st_mode & S_IFMT)
        {
        case S_IFREG:
            printf("Regular\n");
            break;
        case S_IFDIR:
            printf("Directory\n");
            break;
        case S_IFBLK:
            printf("Block\n");
            break;
        case S_IFCHR:
            printf("Character\n");
            break;
        case S_IFIFO:
            printf("FIFO/pipe\n");
            break;
        case S_IFLNK:
            printf("Symbolic link\n");
            break;
        case S_IFSOCK:
            printf("Socket\n");
            break;
        default:
            printf("Unknown\n");
            break;
        }

        // Display file access permissions
        printf("Access permissions: %o\n", file_metadata->st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));

        // Drill down owner, group, and other user permissions in user-friendly table.
        printf("\t\t\tRWX\n");
        printf("Owner %d Permissions:\t", file_metadata->st_uid);
        printf((file_metadata->st_mode & S_IRUSR) ? "x" : " ");
        printf((file_metadata->st_mode & S_IWUSR) ? "x" : " ");
        printf((file_metadata->st_mode & S_IXUSR) ? "x" : " ");
        printf("\n");
        printf("Group %d Permissions:\t", file_metadata->st_gid);
        printf((file_metadata->st_mode & S_IRGRP) ? "x" : " ");
        printf((file_metadata->st_mode & S_IWGRP) ? "x" : " ");
        printf((file_metadata->st_mode & S_IXGRP) ? "x" : " ");
        printf("\n");
        printf("Other Permissions:\t");
        printf((file_metadata->st_mode & S_IROTH) ? "x" : " ");
        printf((file_metadata->st_mode & S_IWOTH) ? "x" : " ");
        printf((file_metadata->st_mode & S_IXOTH) ? "x" : " ");
        printf("\n");
        printf("\n");

        // Display file physical location attributes
        printf(
            "Device %ld inode number %ld has a size of %ld bytes\n",
            file_metadata->st_dev,
            file_metadata->st_ino,
            file_metadata->st_size);
        printf("File stored using %ld 512-byte blocks\n", file_metadata->st_blocks);
        printf("Optimal block size is %ld bytes\n", file_metadata->st_blksize);
        printf("\n");

        // Display file metadata timestamps
        printf("Last accessed on:          %s", ctime(&file_metadata->st_atime));
        printf("Last modified on:          %s", ctime(&file_metadata->st_mtime));
        printf("Metadata last modified on: %s", ctime(&file_metadata->st_ctime));
    }
    else if (argc == 1)
    {
        // Bail out if no argument is provided.
        printf(
            "A filepath was not provided. Please provide a single "
            "file to retrieve metadata for.\n");
        exit(1);
    }
    else
    {
        // Bail out if more than one argument is provided.
        printf(
            "More than two arguments provided. Please provide a single "
            "file to retrieve metadata for.\n");
        exit(1);
    }
}
