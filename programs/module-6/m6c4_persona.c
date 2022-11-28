#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 4096
#define UNPRIVILEGED_FILEPATH "/home/christopher/foo.txt"
#define PRIVILEGED_FILEPATH "/home/cjh/foo.txt"

int main()
{
    uid_t real_uid;
    uid_t effective_uid;
    gid_t real_gid;
    gid_t effective_gid;
    FILE *stream;
    char *privileged_buffer[BUFFER_SIZE];
    char *unprivileged_buffer[BUFFER_SIZE];

    real_uid = getuid();
    real_gid = getgid();
    effective_uid = geteuid();
    effective_gid = getegid();

    printf("     Original Real UID: %d\n", real_uid);
    printf("     Original Real GID: %d\n", real_gid);
    printf("Original Effective UID: %d\n", effective_uid);
    printf("Original Effective GID: %d\n", effective_gid);
    printf("\n");

    // For unprivileged filepath, de-escalate privileges to real UID and GID.
    printf("De-escalating privileges\n");
    if (seteuid(real_uid) < 0)
    {
        perror("Failed to de-escalate privileges to real UID");
        exit(1);
    }
    if (setegid(real_gid) < 0)
    {
        perror("Failed to de-escalate privileges to real GID");
        exit(1);
    }

    printf("     Current Real UID: %d\n", getuid());
    printf("     Current Real GID: %d\n", getgid());
    printf("Current Effective UID: %d\n", geteuid());
    printf("Current Effective GID: %d\n", getegid());
    printf("\n");

    stream = fopen(UNPRIVILEGED_FILEPATH, "r");
    if (stream == NULL)
    {
        perror("Failed to open stream for unprivileged filepath");
        exit(1);
    }
    printf("Contents of %s:\n", UNPRIVILEGED_FILEPATH);
    while (fread(privileged_buffer, 1, BUFFER_SIZE, stream) > 0)
    {
        fwrite(privileged_buffer, 1, BUFFER_SIZE, stdout);
    }
    fclose(stream);
    printf("\n");

    // For privileged filepath, escalate privileges back to effective UID and
    // GID.
    printf("Escalating privileges\n");
    if (seteuid(effective_uid) < 0)
    {
        perror("Failed to escalate privileges to effective UID");
        exit(1);
    }
    if (setegid(effective_gid) < 0)
    {
        perror("Failed to escalate privileges to effective GID");
        exit(1);
    }

    printf("     Current Real UID: %d\n", getuid());
    printf("     Current Real GID: %d\n", getgid());
    printf("Current Effective UID: %d\n", geteuid());
    printf("Current Effective GID: %d\n", getegid());
    printf("\n");

    stream = fopen(PRIVILEGED_FILEPATH, "r");
    if (stream == NULL)
    {
        perror("Failed to open stream for privileged filepath");
        exit(1);
    }
    printf("Contents of %s:\n", PRIVILEGED_FILEPATH);
    while (fread(unprivileged_buffer, 1, BUFFER_SIZE, stream) > 0)
    {
        fwrite(unprivileged_buffer, 1, BUFFER_SIZE, stdout);
    }
    fclose(stream);
}
