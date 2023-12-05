#include "headers.h"

char *relative_path(char *home_directory, char *current_directory)
{
    char *return_directory = create_string();
    size_t home_length = strlen(home_directory);
    size_t current_length = strlen(current_directory);

    if (home_length > current_length)
    {
        // printf("line 13\n");
        return current_directory;
    }
    else
    {
        size_t i = 0;
        int relative = 1;
        while (home_directory[i] != '\0')
        {
            if (home_directory[i] == current_directory[i])
            {
                i++;
            }
            else
            {
                relative = 0;
                break;
            }
        }
        if (relative == 1)
        {
            // printf("yo\n");

            return_directory[0] = '~';
            int j = 1;
            while (current_directory[i] != '\0')
            {
                return_directory[j] = current_directory[i];
                i++, j++;
            }
            return_directory[j] = '\0';
        }
        else
        {
            return current_directory;
        }
    }
    return return_directory;
}