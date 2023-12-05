#include "headers.h"

char *create_string()
{
    char *ret = (char *)malloc(sz * sizeof(char));
    return ret;
}
void update_history(int *current_command_index, int *history_count, char *history[history_sz], char input[sz])
{

    *current_command_index = (*current_command_index + 1) % history_sz;
    free(history[*current_command_index]);
    history[*current_command_index] = (char *)calloc(sz, sizeof(char));
    history[*current_command_index] = strdup(input);
    if (*history_count < 15)
        *history_count = *history_count + 1;
}
void restore_history(int *current_command_index, int *history_count, char *history[history_sz])
{
    FILE *pastevents_file = fopen("pastevents.txt", "r");
    if (pastevents_file != NULL)
    {
        int i = 0;
        char *history_line = create_string();
        while (fgets(history_line, sz, pastevents_file) != NULL)
        {
            // printf("line = %s", history_line);
            history[i] = strdup(history_line);
            i++;
        }
        *history_count = i;
        *current_command_index = (i - 1) % 15;
    }
    else
    {
        perror("Failed to restore history");
    }
}

int main()
{
    char *home_directory = create_string();
    char *current_directory = create_string();
    char *system_name = create_string();
    char *user_name = create_string();
    char *previous_directory = create_string();

    char *system_command_name = (char *)calloc(sz, sizeof(char));
    int time_taken = 0;

    int current_command_index = -1;
    int history_count = 0;
    char *history[history_sz];

    for (int i = 0; i < history_sz; i++)
    {
        history[i] = create_string();
    }
    // RESTORE HISTORY
    restore_history(&current_command_index, &history_count, history);
    getcwd(home_directory, sz);

    // LINKED LIST FOR BACKGROUND PROCESSES
    ptrnode linkedlist = createnode(0, "abc");

    while (1)
    {
        prompt(user_name, system_name, home_directory, current_directory, previous_directory, system_command_name, &time_taken);
        // CHECK STATUS OF BACKGROUND PROCESSES
        char input[sz];
        fgets(input, sz, stdin);

        deletenode(linkedlist);

        // UPDATING HISTORY
        if (strlen(input) > 1) // CONDITION REMOVES EMPTY STRINGS
        {
            int skip_update = 0;
            char *input_copy = strdup(input);
            input_copy[strcspn(input_copy, "\n")] = '\0';

            ////////////////////////////////
            // // HANDLES "pastevents"
            // if (strcmp(input_copy, "pastevents") == 0)
            //     skip_update = 1;

            // // HANDLES "pastevents purge"
            // char *word1 = strtok_r(input_copy, " \t\n\0", &input_copy);
            // char *word2 = strtok_r(input_copy, " \t\n\0", &input_copy);
            // char *word3 = strtok_r(input_copy, " \t\n\0", &input_copy);
            // if (strcmp(word1, "pastevents") == 0 && word2 != NULL && strcmp(word2, "purge") == 0 && word3 == NULL)
            //     skip_update = 1;

            // // HANDLES "pastevents execute"
            // if (strcmp(word1, "pastevents") == 0 && word2 != NULL && strcmp(word2, "execute") == 0)
            // {
            //     skip_update = 1;
            // }
            ////////////////////////////////

            // HANDLES PASTEVENTS
            char delims[] = " ;&\t\n\0";
            char *word_input_copy = strtok_r(input_copy, delims, &input_copy);
            while (word_input_copy != NULL)
            {
                if (strcmp(word_input_copy, "pastevents") == 0)
                    skip_update = 1;
                word_input_copy = strtok_r(input_copy, delims, &input_copy);
            }

            // HANDLES repition
            if (current_command_index >= 0 && strcmp(input, history[current_command_index]) == 0)
                skip_update = 1;
            // REMAINING CASES
            if (!skip_update)
                update_history(&current_command_index, &history_count, history, input);
        }
        // HISTORY UPDATED

        input[strcspn(input, "\n")] = '\0';

        input_function(input, home_directory, current_directory, previous_directory, history, history_count, current_command_index, &history_count, &current_command_index, 0, system_command_name, &time_taken, linkedlist);

        // printf("time_taken = %d\n", time_taken);
        // printf("system_command_name = %s\n", system_command_name);
    }
}
