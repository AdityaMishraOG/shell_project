#include "headers.h"

int alphasort(const struct dirent **entry1, const struct dirent **entry2)
{
    return strcmp((*entry1)->d_name, (*entry2)->d_name);
}

void print_file_permissions(mode_t permissions)
{
    if (S_ISDIR(permissions))
        printf("d");
    else
        printf("-");

    if (permissions != 0 && (permissions & S_IRUSR))
        printf("r");
    else
        printf("-");

    if (permissions != 0 && (permissions & S_IWUSR))
        printf("w");
    else
        printf("-");

    if (permissions != 0 && (permissions & S_IXUSR))
        printf("x");
    else
        printf("-");

    if (permissions != 0 && (permissions & S_IRGRP))
        printf("r");
    else
        printf("-");

    if (permissions != 0 && (permissions & S_IWGRP))
        printf("w");
    else
        printf("-");

    if (permissions != 0 && (permissions & S_IXGRP))
        printf("x");
    else
        printf("-");

    if (permissions != 0 && (permissions & S_IROTH))
        printf("r");
    else
        printf("-");

    if (permissions != 0 && (permissions & S_IWOTH))
        printf("w");
    else
        printf("-");

    if (permissions != 0 && (permissions & S_IXOTH))
        printf("x");
    else
        printf("-");
}

void peek_util(char *final_location, int a, int l)
{
    DIR *final_directory;
    struct dirent **list_of_entries;
    struct dirent *entry;

    final_directory = opendir(final_location);
    if (final_directory != NULL)
    {
        int entries_count = scandir(final_location, &list_of_entries, NULL, alphasort);
        for (int i = 0; i < entries_count; i++)
        {
            entry = list_of_entries[i];
            if (a == 0 && l == 0)
            {
                struct stat file_data;
                // CREATING ENTRY PATH
                char *entry_location = (char *)calloc(sz, sizeof(char));
                int k = 0;
                while (final_location[k] != '\0')
                {
                    entry_location[k] = final_location[k];
                    k++;
                }
                entry_location[k] = '/';
                k++;
                int l = 0;
                while (entry->d_name[l] != '\0')
                {
                    entry_location[k] = entry->d_name[l];
                    k++;
                    l++;
                }
                // ENTRY PATH CREATED
                if (stat(entry_location, &file_data) == 0)
                {

                    if (entry->d_name[0] != '.')
                    {
                        // printf("file_data.st_mode = %d\n", file_data.st_mode);
                        if (S_ISDIR(file_data.st_mode)) // DIRECTORY
                        {
                            printf(BLUE "%s\n" RESET, entry->d_name);
                        }
                        else if (file_data.st_mode & S_IXUSR) // EXECUTABLE
                        {
                            printf(GREEN "%s\n" RESET, entry->d_name);
                        }
                        else // FILE
                        {
                            printf(WHITE "%s\n" RESET, entry->d_name);
                        }
                    }
                }
            }
            else if (a == 1 && l == 0)
            {

                struct stat file_data;
                // CREATING ENTRY PATH
                char *entry_location = (char *)calloc(sz, sizeof(char));
                int k = 0;
                while (final_location[k] != '\0')
                {
                    entry_location[k] = final_location[k];
                    k++;
                }
                entry_location[k] = '/';
                k++;
                int l = 0;
                while (entry->d_name[l] != '\0')
                {
                    entry_location[k] = entry->d_name[l];
                    k++;
                    l++;
                }
                // ENTRY PATH CREATED
                if (stat(entry_location, &file_data) == 0)
                {

                    // printf("file_data.st_mode = %d\n", file_data.st_mode);
                    if (S_ISDIR(file_data.st_mode)) // DIRECTORY
                    {
                        printf(BLUE "%s\n" RESET, entry->d_name);
                    }
                    else if (file_data.st_mode & S_IXUSR) // EXECUTABLE
                    {
                        printf(GREEN "%s\n" RESET, entry->d_name);
                    }
                    else // FILE
                    {
                        printf(WHITE "%s\n" RESET, entry->d_name);
                    }
                }
            }
            else if (a == 0 && l == 1)
            {
                if (entry->d_name[0] != '.')
                {
                    struct stat file_data;
                    // CREATING ENTRY PATH
                    char *entry_location = (char *)calloc(sz, sizeof(char));
                    int k = 0;
                    while (final_location[k] != '\0')
                    {
                        entry_location[k] = final_location[k];
                        k++;
                    }
                    entry_location[k] = '/';
                    k++;
                    int l = 0;
                    while (entry->d_name[l] != '\0')
                    {
                        entry_location[k] = entry->d_name[l];
                        k++;
                        l++;
                    }
                    // ENTRY PATH CREATED
                    if (stat(entry_location, &file_data) == 0)
                    {
                        struct passwd *password = getpwuid(file_data.st_uid);
                        struct group *group_id = getgrgid(file_data.st_gid);

                        char *date_and_time = (char *)calloc(sz, sizeof(char));
                        strftime(date_and_time, sizeof(date_and_time), "%b %d %H:%M", localtime(&file_data.st_mtime));

                        print_file_permissions(file_data.st_mode);
                        printf(" %ld %s %s %ld %s ", file_data.st_nlink, password->pw_name, group_id->gr_name, file_data.st_size, date_and_time);

                        if (S_ISDIR(file_data.st_mode)) // DIRECTORY
                        {
                            printf(BLUE " %s\n" RESET, entry->d_name);
                        }
                        else if (file_data.st_mode & S_IXUSR) // EXECUTABLE
                        {
                            printf(GREEN " %s\n" RESET, entry->d_name);
                        }
                        else // FILE
                        {
                            printf(WHITE " %s\n" RESET, entry->d_name);
                        }
                    }
                    else
                    {
                        perror("stat");
                    }
                }
            }
            else
            {
                struct stat file_data;
                // CREATING ENTRY PATH
                char *entry_location = (char *)calloc(sz, sizeof(char));
                int k = 0;
                while (final_location[k] != '\0')
                {
                    entry_location[k] = final_location[k];
                    k++;
                }
                entry_location[k] = '/';
                k++;
                int l = 0;
                while (entry->d_name[l] != '\0')
                {
                    entry_location[k] = entry->d_name[l];
                    k++;
                    l++;
                }
                // ENTRY PATH CREATED
                if (stat(entry_location, &file_data) == 0)
                {
                    struct passwd *password = getpwuid(file_data.st_uid);
                    struct group *group_id = getgrgid(file_data.st_gid);

                    char *date_and_time = (char *)calloc(sz, sizeof(char));
                    strftime(date_and_time, sizeof(date_and_time), "%b %d %H:%M", localtime(&file_data.st_mtime));

                    print_file_permissions(file_data.st_mode);
                    printf(" %ld %s %s %ld %s ", file_data.st_nlink, password->pw_name, group_id->gr_name, file_data.st_size, date_and_time);

                    if (S_ISDIR(file_data.st_mode)) // DIRECTORY
                    {
                        printf(BLUE " %s\n" RESET, entry->d_name);
                    }
                    else if (file_data.st_mode & S_IXUSR) // EXECUTABLE
                    {
                        printf(GREEN " %s\n" RESET, entry->d_name);
                    }
                    else // FILE
                    {
                        printf(WHITE " %s\n" RESET, entry->d_name);
                    }
                }
                else
                {
                    perror("stat");
                }
            }
        }
        closedir(final_directory);
    }
    else
    {
        perror("final_directory");
        return;
    }
}

void peek(char *path_string, char *home_directory, char *current_directory, char *previous_directory, int a, int l)
{

    if (path_string[0] == '~')
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
        while (path_string[j] != '\0')
        {
            final_location[i] = path_string[j];
            i++;
            j++;
        }
        // DESTINATION STRING CREATED
        peek_util(final_location, a, l);
        // printf("final_location = %s\n", final_location);
    }
    else if (path_string[0] == '.' && path_string[1] != '.')
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
        while (path_string[j] != '\0')
        {
            final_location[i] = path_string[j];
            i++;
            j++;
        }
        final_location[i] = '\0';
        // DESTINATION STRING CREATED
        peek_util(final_location, a, l);
        // printf("final_location = %s\n", final_location);
    }
    else if (path_string[0] == '.' && path_string[1] == '.')
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
        while (path_string[j] != '\0')
        {
            final_location[i] = path_string[j];
            i++;
            j++;
        }
        final_location[i] = '\0';
        // DESTINATION STRING CREATED
        peek_util(final_location, a, l);
        // printf("final_location = %s\n", final_location);
    }
    else if (path_string[0] == '/')
    {
        // CREATING DESTINATION STRING
        char *final_location = (char *)calloc(sz, sizeof(char));
        strcpy(final_location, path_string);
        // DESTINATION STRING CREATED
        peek_util(final_location, a, l);
        // printf("final_location = %s\n", final_location);
    }
    else if (path_string[0] == '-')
    {
        // peek(previous_directory, home_directory, current_directory, previous_directory, a, l);
        peek_util(path_string, a, l);
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
        while (path_string[j] != '\0')
        {
            final_location[i] = path_string[j];
            i++;
            j++;
        }
        // DESTINATION STRING CREATED
        peek_util(final_location, a, l);
        // printf("final_location = %s\n", final_location);
    }
}