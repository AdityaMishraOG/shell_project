#include "headers.h"
#define MAX_DEPTH 3

void seek_util(int d, int e, int f, char *search, char *target_location, char *home_directory, char *current_directory, char *outermost_target_location, int *match_found_files, int *match_found_directories)
{
    DIR *target_directory = opendir(target_location);
    struct dirent *entry;

    if (current_directory != NULL)
    {
        while ((entry = readdir(target_directory)) != NULL)
        {
            char *entry_name = strdup(entry->d_name);
            // IGNORE ENTRIES STARTING WITH .
            if (entry_name[0] == '.')
            {
                continue;
            }
            // FINDING PATH OF THE ENTRY
            char *entry_path = (char *)calloc(sz, sizeof(char));
            int i = 0;
            while (target_location[i] != '\0')
            {
                entry_path[i] = target_location[i];
                i++;
            }
            entry_path[i] = '/';
            i++;
            int j = 0;
            while (entry_name[j] != '\0')
            {
                entry_path[i] = entry_name[j];
                i++;
                j++;
            }
            // ENTRY PATH FOUND

            struct stat file_data;
            if (stat(entry_path, &file_data) != -1)
            {
                // FINDING BASENAME
                char *base_name = strdup(entry_name);
                int i = 0;
                while (base_name[i] != '\0' && base_name[i] != '.')
                {
                    i++;
                }
                if (base_name[i] == '.')
                {
                    base_name[i] = '\0';
                }
                // BASENAME FOUND

                if (strcmp(base_name, search) == 0)
                {
                    // FOUND AN ENTRY WITH NAME
                    // UPDATING MATCH FOUND VARIABLES
                    if (S_ISDIR(file_data.st_mode))
                    {
                        *match_found_directories += 1;
                    }
                    else
                    {
                        *match_found_files += 1;
                    }

                    // FINDING RELATIVE PATH OF THE THE  ENTRY
                    char *relative_entry_path = (char *)calloc(sz, sizeof(char));
                    int i = 0;
                    while (outermost_target_location[i] != '\0' && (entry_path[i] == outermost_target_location[i]))
                    {
                        i++;
                    }
                    int j = 1;
                    relative_entry_path[0] = '.';
                    while (entry_path[j] != '\0')
                    {
                        relative_entry_path[j] = entry_path[i];
                        i++;
                        j++;
                    }
                    // RELLATIVE PATH FOUND
                    // CONDITIONS FOR VARIOUS FLAG VALUES OF d AND f
                    if ((d == 1 && f == 1) || (d == 0 && f == 0))
                    {
                        // PRINTS BOTH DIRECTORIES AND FILES
                        if (S_ISDIR(file_data.st_mode))
                            printf(BLUE "%s\n" RESET, relative_entry_path);
                        else
                            printf(GREEN "%s\n" RESET, relative_entry_path);
                    }
                    else if (d == 1 && f == 0)
                    {
                        // PRINTS DIRECTORIES ONLY
                        if (S_ISDIR(file_data.st_mode))
                        {
                            printf(BLUE "%s\n" RESET, relative_entry_path);
                        }
                    }
                    else if (d == 0 && f == 1)
                    {
                        // PRINTS FILES ONLY
                        if (!S_ISDIR(file_data.st_mode))
                        {
                            printf(GREEN "%s\n" RESET, relative_entry_path);
                        }
                    }
                }
                // CHECKS IF THE ENTRY IS A DIRECTORY
                if (S_ISDIR(file_data.st_mode))
                {
                    // RECURSIVELY SEARCHES FOR THE SEARCH TERM IN THIS DIRECTORY
                    seek_util(d, e, f, search, entry_path, home_directory, current_directory, outermost_target_location, match_found_files, match_found_directories);
                }
            }
            else
            {
                perror("Entry in Target Directory not found");
            }
        }
    }
    else
    {
        perror("Target Directory not found");
    }
    closedir(target_directory);
}

char *seek_e_flag(int d, int e, int f, char *search, char *target_location, char *home_directory, char *current_directory, char *outermost_target_location)
{
    DIR *target_directory = opendir(target_location);
    struct dirent *entry;

    // PATH TO BE RETURNED
    if (current_directory != NULL)
    {
        while ((entry = readdir(target_directory)) != NULL)
        {
            char *entry_name = strdup(entry->d_name);
            // IGNORE ENTRIES STARTING WITH .
            if (entry_name[0] == '.')
            {
                continue;
            }
            // FINDING PATH OF THE ENTRY
            char *entry_path = (char *)calloc(sz, sizeof(char));
            int i = 0;
            while (target_location[i] != '\0')
            {
                entry_path[i] = target_location[i];
                i++;
            }
            entry_path[i] = '/';
            i++;
            int j = 0;
            while (entry_name[j] != '\0')
            {
                entry_path[i] = entry_name[j];
                i++;
                j++;
            }
            // ENTRY PATH FOUND

            struct stat file_data;
            if (stat(entry_path, &file_data) != -1)
            {
                // FINDING BASENAME
                char *base_name = strdup(entry_name);
                int i = 0;
                while (base_name[i] != '\0' && base_name[i] != '.')
                {
                    i++;
                }
                if (base_name[i] == '.')
                {
                    base_name[i] = '\0';
                }
                // BASENAME FOUND

                if (strcmp(base_name, search) == 0)
                {
                    // FOUND AN ENTRY WITH NAME

                    // FINDING RELATIVE PATH OF THE ENTRY
                    char *relative_entry_path = (char *)calloc(sz, sizeof(char));
                    int i = 0;
                    while (outermost_target_location[i] != '\0' && (entry_path[i] == outermost_target_location[i]))
                    {
                        i++;
                    }
                    int j = 1;
                    relative_entry_path[0] = '.';
                    while (entry_path[j] != '\0')
                    {
                        relative_entry_path[j] = entry_path[i];
                        i++;
                        j++;
                    }

                    // CONDITIONS FOR VARIOUS FLAG VALUES OF d AND f
                    if ((d == 0 && f == 0))
                    {
                        // PRINTS BOTH DIRECTORIES AND FILES
                        // printf("%s\n", relative_entry_path);
                        return relative_entry_path;
                    }
                    else if (d == 1 && f == 0)
                    {
                        // PRINTS DIRECTORIES ONLY
                        if (S_ISDIR(file_data.st_mode))
                        {
                            // printf("%s\n", relative_entry_path);
                            return relative_entry_path;
                        }
                    }
                    else if (d == 0 && f == 1)
                    {
                        // PRINTS FILES ONLY
                        if (!S_ISDIR(file_data.st_mode))
                        {
                            return relative_entry_path;
                        }
                    }
                    // RELATIVE PATH FOUND
                }
                // CHECKS IF THE ENTRY IS A DIRECTORY
                if (S_ISDIR(file_data.st_mode))
                {
                    // RECURSIVELY SEARCHES FOR THE SEARCH TERM IN THIS DIRECTORY
                    char *ret = seek_e_flag(d, e, f, search, entry_path, home_directory, current_directory, outermost_target_location);
                    if (f && !d) // LOOKING FOR FILE ONLY
                    {

                        if (!S_ISDIR(file_data.st_mode))
                        {
                            if (ret)
                                return ret;
                        }
                    }
                    else if (d)
                    {
                        if (S_ISDIR(file_data.st_mode))
                        {
                            if (ret)
                                return ret;
                        }
                    }
                    if (ret)
                        return ret;
                }
            }
            else
            {
                perror("Entry in Target Directory not found");
            }
        }
    }
    else
    {
        perror("Target Directory not found");
    }
    closedir(target_directory);
}

void seek(int d, int e, int f, char *search, char *target_directory, char *home_directory, char *current_directory)
{
    int match_found_files = 0;
    int match_found_directories = 0;
    char *target_location = absolute_path(target_directory, home_directory, current_directory);
    seek_util(d, e, f, search, target_location, home_directory, current_directory, target_location, &match_found_files, &match_found_directories);

    // printf("match_found_files = %d\n", match_found_files);
    // printf("match_found_directories = %d\n", match_found_directories);

    int match_found_total = match_found_files + match_found_directories;
    if (!match_found_total)
    {
        printf("No match found!\n");
        return;
    }
    
    if (d == 1 && match_found_directories == 0)
    {
        printf("No match found!\n");
        return;
    }
    else if (f == 1 && match_found_files == 0)
    {
        printf("No match found!\n");
        return;
    }

    if (e)
    {
        if ((d == 1 && match_found_directories == 1) || (f == 1 && match_found_files == 1) || (match_found_total == 1))
        {
            // ACTION FOR e FLAG
            if ((f == 1 && match_found_files == 1) || (match_found_directories == 0 && match_found_files == 1))
            {
                // FILE FOUND
                char *file_location = seek_e_flag(d, e, f, search, target_location, home_directory, current_directory, target_location);
                if (file_location == NULL)
                {
                    printf("No matches found\n");
                    return;
                }
                // printf("%s file location found in e flag\n", file_location);

                char *final_file_location = (char *)calloc(sz, sizeof(char));
                int i2 = 0;
                while (target_directory[i2] != '\0')
                {
                    final_file_location[i2] = target_directory[i2];
                    i2++;
                }
                int j2 = 1;
                while (file_location[j2] != '\0')
                {
                    final_file_location[i2] = file_location[j2];
                    i2++;
                    j2++;
                }
                // printf("final_file_loc = %s\n", final_file_location);

                // NOW WE EXTRACT THE FILE DATA
                struct stat file_data;
                if (stat(final_file_location, &file_data) != -1)
                {
                    // WE CHECK IF THE FILE HAS PERMISSIONS
                    if (S_IRUSR && file_data.st_mode)
                    {
                        // NOW, WE TRY TO PRINT THE CONTENTS OF THE FILE
                        int fd = open(final_file_location, O_RDONLY);
                        // printf("fd = %d\n", fd);
                        if (fd != -1)
                        {
                            char *line = (char *)calloc(sz, sizeof(char));
                            int bytes_read;
                            while ((bytes_read = read(fd, line, sz)) > 0)
                            {
                                line[bytes_read] = '\0';
                                printf("%s\n", line);
                            }
                        }
                        else
                        {
                            perror("File could not be accessed");
                        }
                    }
                    else
                    {
                        printf("Permission to read file denied\n");
                    }
                }
                else
                {
                    perror("File could not be accessed");
                }
            }
            else if ((d == 1 && match_found_directories == 1) || (match_found_files == 0 && match_found_directories == 1))
            {
                // DIRECTORY FOUND
                char *directory_location = seek_e_flag(d, e, f, search, target_location, home_directory, current_directory, target_location);
                // printf("directory_location = %s\n", directory_location);
                int ret = chdir(directory_location);
                if (ret == 0)
                {
                    printf("Current Working Directory changed successfully!\n");
                }
                else
                {
                    perror("Unable to change directory!");
                }
            }
        }
    }
}