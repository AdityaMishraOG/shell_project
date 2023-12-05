#include "headers.h"

char *absolute_path(char *input_location, char *home_directory, char *current_directory)
{

    if (input_location[0] == '~')
    {
        // CREATING DESTINATION STRING
        char *final_location = (char *)calloc(sz, sizeof(char));
        int i = 0;
        while (home_directory[i] != '\0')
        {
            final_location[i] = home_directory[i];
            i++;
        }
        int j = 1;
        while (input_location[j] != '\0')
        {
            final_location[i] = input_location[j];
            i++;
            j++;
        }
        // DESTINATION STRING CREATED
        return final_location;
        // printf("final_location = %s\n", final_location);
    }
    else if (input_location[0] == '.' && input_location[1] != '.')
    {
        // CREATING DESTINATION STRING
        char *final_location = (char *)calloc(sz, sizeof(char));
        int i = 0;
        while (current_directory[i] != '\0')
        {
            final_location[i] = current_directory[i];
            i++;
        }
        int j = 1;
        while (input_location[j] != '\0')
        {
            final_location[i] = input_location[j];
            i++;
            j++;
        }
        final_location[i] = '\0';
        // DESTINATION STRING CREATED
        return final_location;
        // printf("final_location = %s\n", final_location);
    }
    else if (input_location[0] == '.' && input_location[1] == '.')
    {
        // GETTING PARENT DIRECTORY
        chdir("..");
        char *parent_directory = (char *)calloc(sz, sizeof(char));
        getcwd(parent_directory, sz);
        if (chdir(current_directory) == 0)
        {
            // printf("original directory restored!\n");
        }
        else
        {
            perror("chdir");
        }

        // CREATING DESTINATION STRING
        char *final_location = (char *)calloc(sz, sizeof(char));
        int i = 0;
        while (parent_directory[i] != '\0')
        {
            final_location[i] = parent_directory[i];
            i++;
        }
        int j = 2;
        while (input_location[j] != '\0')
        {
            final_location[i] = input_location[j];
            i++;
            j++;
        }
        final_location[i] = '\0';
        // DESTINATION STRING CREATED
        return final_location;
        // printf("final_location = %s\n", final_location);
    }
    else if (input_location[0] == '/')
    {
        // CREATING DESTINATION STRING
        char *final_location = (char *)calloc(sz, sizeof(char));
        strcpy(final_location, input_location);
        // DESTINATION STRING CREATED
        return final_location;
        // printf("final_location = %s\n", final_location);
    }
    else
    {
        // CREATING DESTINATION STRING
        char *final_location = (char *)calloc(sz, sizeof(char));
        int i = 0;
        while (home_directory[i] != '\0')
        {
            final_location[i] = home_directory[i];
            i++;
        }
        int j = 0;
        while (input_location[j] != '\0')
        {
            final_location[i] = input_location[j];
            i++;
            j++;
        }
        // DESTINATION STRING CREATED
        return final_location;
        // printf("final_location = %s\n", final_location);
    }
}