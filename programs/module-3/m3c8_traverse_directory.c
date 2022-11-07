#include <dirent.h>
// include limits for PATH_MAX
#include <limits.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print_file_name_with_depth(char filename[], int depth)
{
    for (int i = 0; i < depth; i++)
    {
        printf("  ");
    }
    printf("%s\n", filename);
}

void traverse_directory(char directory_path[], int depth)
{
    DIR *directory;
    if ((directory = opendir(directory_path)) == NULL)
    {
        perror("Failed to open directory");
        exit(1);
    }
    struct dirent *directory_entry;
    while ((directory_entry = readdir(directory)) != NULL)
    {
        // If entry is another directory, recursively call traverse_directory()
        if ((directory_entry->d_type == DT_DIR))
        {
            // Don't try to traverse current directory (".") or parent directory ("..")
            int current_directory = strcmp(directory_entry->d_name, ".");
            int parent_directory = strcmp(directory_entry->d_name, "..");
            if ((current_directory != 0) && (parent_directory != 0))
            {
                print_file_name_with_depth(directory_entry->d_name, depth);
                char new_directory_path[PATH_MAX];
                strcpy(new_directory_path, directory_path);
                strcat(new_directory_path, "/");
                strcat(new_directory_path, directory_entry->d_name);
                traverse_directory(new_directory_path, depth + 1);
            }
        }
        else
        {
            print_file_name_with_depth(directory_entry->d_name, depth);
        }
    }
    closedir(directory);
}

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        int ret;
        struct stat *directory_metadata = malloc(sizeof(struct stat));
        if ((ret = stat(argv[1], directory_metadata)) < 0)
        {
            perror("Failed to retrieve metadata for directory");
            exit(1);
        }
        if ((directory_metadata->st_mode & S_IFMT) != S_IFDIR)
        {
            // Bail out if argument is not a directory.
            printf(
                "Argument %s provided is not a directory. Please provide a single "
                "directory to traverse.\n",
                argv[1]);
            exit(1);
        }
        // Argument is a directory - call traverse_directory()
        traverse_directory(argv[1], 0);
    }
    else if (argc == 1)
    {
        // Bail out if no argument is provided.
        printf(
            "A directory was not provided. Please provide a single "
            "directory to traverse.\n");
        exit(1);
    }
    else
    {
        // Bail out if more than one argument is provided.
        printf(
            "More than two arguments provided. Please provide a single "
            "directory to traverse.\n");
        exit(1);
    }
}
