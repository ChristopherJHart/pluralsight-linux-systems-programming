#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 16348

int main()
{
    FILE *source_text_output, *more_pager_input;
    char buffer[BUFFER_SIZE];

    // Create a pipe that will let us read data from source file using readable
    // end of a pipe to the "cat" command
    source_text_output = popen("cat m5c9_source.txt", "r");
    if (source_text_output == NULL)
    {
        perror("Error while opening source text file");
        exit(1);
    }

    // Create a pipe that will let us write data from source file into the
    // writeable end of a pipe to the "more" program
    more_pager_input = popen("more", "w");
    if (more_pager_input == NULL)
    {
        perror("Error while opening pipe to more");
        exit(1);
    }

    // Continuously read data from pipe to source text
    while ((fread(buffer, BUFFER_SIZE, 1, source_text_output) > 0))
    {
        // Write data to pipe leading to "more" program, which will paginate
        // output for us.
        fwrite(buffer, BUFFER_SIZE, 1, more_pager_input);
    }

    // Close pipes once finished.
    pclose(source_text_output);
    pclose(more_pager_input);
}
