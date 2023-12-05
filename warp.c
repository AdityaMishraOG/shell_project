#include "headers.h"

void warp(char *input_string, char *home_directory, char *current_directory, char *previous_directory)
{
    if (input_string[0] == '~')
    {
        if (chdir(home_directory) == 0)
        {
            // CREATING DESTINATION STRING
            char *final_location = (char *)calloc(1000, sizeof(char));
            int i = 2;
            while (input_string[i] != '\0')
            {
                final_location[i - 2] = input_string[i];
                i++;
            }
            // final_location[i - 3] = '\0';
            final_location[i - 2] = '\0';
            // DESTINATION STRING CREATED

            if (i == 2)
            {
                // HANDLES ~ INPUT ONLY
                return;
            }
            if (chdir(final_location) == 0)
            {
                // HANDLES OTHER CASES
            }
            else
            {
                // HANDLES DIRECTORY NOT FOUND
                chdir(current_directory);
                perror("chdir");
            }
        }
        else
        {
            perror("chdir");
        }
        return;
    }
    else if (input_string[0] == '.' && input_string[1] != '.')
    {
        // CREATING DESTINATION STRING
        char *final_location = (char *)calloc(1000, sizeof(char));
        int i = 2;
        while (input_string[i] != '\0')
        {
            final_location[i - 2] = input_string[i];
            i++;
        }
        // final_location[i - 3] = '\0';
        final_location[i - 2] = '\0';
        // DESTINATION STRING CREATED

        if (i == 2)
        {
            // HANDLES . INPUT ONLY
            return;
        }
        if (chdir(final_location) == 0)
        {
            // HANDLES OTHER CASES
        }
        else
        {
            // HANDLES DIRECTORY NOT FOUND
            perror("chdir");
        }
        return;
    }
    else if (input_string[0] == '.' && input_string[1] == '.')
    {
        chdir("..");
        // CREATING DESTINATION STRING
        char *final_location = (char *)calloc(sz, sizeof(char));
        int i = 3;
        while (input_string[i] != '\0')
        {
            final_location[i - 3] = input_string[i];
            i++;
        }
        // final_location[i - 4] = '\0';
        final_location[i - 3] = '\0';
        // DESTINATION STRING CREATED

        if (i == 3)
        {
            // HANDLES .. INPUT ONLY
            return;
        }

        if (chdir(final_location) == 0)
        {
            // HANDLES OTHER CASES
        }
        else
        {
            // HANDLES DIRECTORY NOT FOUND
            perror("chdir");
        }
    }
    else if (input_string[0] == '\\')
    {
        // input_string[strlen(input_string) - 1] = '\0';
        if (chdir(input_string) == 0)
        {
            // HANDLES / CASES
        }
        else
        {
            perror("chdir");
        }
    }
    else if (input_string[0] == '-')
    {
        if (previous_directory == NULL)
            return;
        chdir(previous_directory);
        return;
    }
    else
    {
        // CREATING DESTINATION STRING
        // input_string[strlen(input_string) - 1] = '\0';
        // DESTINATION STRING CREATED
        if (chdir(input_string) == 0)
        {
            // HANDLES ALL CASES
        }
        else
        {
            // HANDLES DIRECTORY NOT FOUND
            perror("chdir");
        }
        return;
    }
}
