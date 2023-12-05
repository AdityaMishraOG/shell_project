#include "headers.h"
// #include "relative_path.c"

void prompt(char *user_name, char *system_name, char *home_directory, char *current_directory, char *previous_directory, char *system_command_name, int *ptr_time_taken)
{
    // Do not hardcode the prmopt
    strcpy(user_name, getlogin());
    gethostname(system_name, sz);
    // previous_directory = strdup(current_directory)

    char *next_directory = (char *)calloc(sz, sizeof(char));
    getcwd(next_directory, sz);

    if (strcmp(next_directory, current_directory) != 0)
    {
        strcpy(previous_directory, current_directory);
        strcpy(current_directory, next_directory);
    }

    // printf("current_directory = %s\n", current_directory);
    // printf("previous_dirctory = %s\n", previous_directory);

    char *print_directory = relative_path(home_directory, current_directory);
    if (strlen(system_command_name) && ptr_time_taken)
    {
        printf(YELLOW "<%s@%s:%s %s : %ds> " RESET, user_name, system_name, print_directory, system_command_name, *ptr_time_taken);
        strcpy(system_command_name, "");
        *ptr_time_taken = 0;
    }
    else
    {
        printf(YELLOW "<%s@%s:%s> " RESET, user_name, system_name, print_directory);
    }
}
