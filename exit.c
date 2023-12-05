#include "headers.h"

void exit_function(char *history[history_sz], int history_count, int current_command_index)
{
    int fd = open("pastevents.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd != -1)
    {
        int i = current_command_index;
        i = (current_command_index - history_count + history_sz + 1) % history_sz;
        int counter = 0;
        while (counter < history_sz)
        {
            int bytes_written = write(fd, history[i], strlen(history[i]));
            if (bytes_written == -1)
            {
                perror("Failed to save history");
                exit(1);
            }

            i = (i + 1) % history_sz;
            counter++;
        }
        close(fd);
        exit(0);
    }
    else
    {
        perror("Failed to save history");
        exit(1);
    }
}