#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/inotify.h>
#include <sys/stat.h>

#define BUFFER_SIZE (250 * ((sizeof(struct inotify_event)) + NAME_MAX + 1))

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        // Fetch metadata for user-provided directory
        int ret;
        struct stat *file_metadata = malloc(sizeof(struct stat));
        if ((ret = stat(argv[1], file_metadata)) < 0)
        {
            perror("Failed to retrieve metadata for file");
            exit(1);
        }

        // Validate user-provided directory is indeed a directory
        if ((file_metadata->st_mode & S_IFMT) != S_IFDIR)
        {
            // Bail out if argument is not a directory.
            printf(
                "Argument %s provided is not a directory. "
                "Please provide a directory to monitor.\n",
                argv[1]);
            exit(1);
        }

        // Remove trailing slash from filepath if present
        char directory[PATH_MAX];
        strcpy(directory, argv[1]);
        if (directory[strlen(directory) - 1] == '/')
        {
            directory[strlen(directory) - 1] = 0;
        }

        // Initialize inotify API
        int notify_fd;
        if ((notify_fd = inotify_init()) < 0)
        {
            perror("Failed to initialize inotify API");
            exit(1);
        }

        // Add user-provided directory to inotify watchlist
        int events_mask = IN_ACCESS | IN_CREATE | IN_CLOSE_WRITE | IN_DELETE;
        if ((inotify_add_watch(notify_fd, directory, events_mask)) < 0)
        {
            perror("Failed to watch directory for changes");
            exit(1);
        }

        // Enter infinite loop, continuously reading from inotify event queue
        char event_buffer[BUFFER_SIZE];
        struct inotify_event *event;
        while (1)
        {
            int bytes_read = read(notify_fd, event_buffer, BUFFER_SIZE);
            for (char *data_read = event_buffer; data_read < event_buffer + bytes_read;)
            {
                // Cast data read from inotify to an event structure
                event = (struct inotify_event *)data_read;
                data_read += sizeof(struct inotify_event) + event->len;

                // Categorize event and print output to stdout accordingly
                if (event->mask & IN_ACCESS)
                {
                    printf("File %s/%s was accessed.\n", directory, event->name);
                }
                if (event->mask & IN_CREATE)
                {
                    printf("File %s/%s was created.\n", directory, event->name);
                }
                if (event->mask & IN_CLOSE_WRITE)
                {
                    printf("File %s/%s was modified.\n", directory, event->name);
                }
                if (event->mask & IN_DELETE)
                {
                    printf("File %s/%s was deleted.\n", directory, event->name);
                }
            }
        }
    }
    else if (argc == 1)
    {
        // Bail out if no argument is provided.
        printf(
            "A file or directory was not provided. Please provide a file or "
            "directory to monitor.\n");
        exit(1);
    }
    else
    {
        // Bail out if more than one argument is provided.
        printf(
            "More than two arguments provided. Please provide a single file or "
            "directory to monitor.\n");
        exit(1);
    }
}
