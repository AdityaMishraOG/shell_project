#include "headers.h"
#include "input.h"

void pastevents(int history_count, int current_command_index, char *history[history_sz])
{
    // printf("history count = %d\n", history_count);

    if (history_count >= 15)
    {
        int i = (current_command_index + 1) % 15;
        int count = 0;

        while (count < 15)
        {
            printf("%d    %s", count + 1, history[i]);
            i = (i + 1) % 15;
            count++;
        }
    }
    else
    {
        for (int i = 0; i < history_count; i++)
        {
            printf("%d    %s", i + 1, history[i]);
        }
    }
}

void pastevents_purge(int *ptr_history_count, int *ptr_current_command_index)
{
    *ptr_history_count = 0;
    *ptr_current_command_index = -1;
    FILE *pastevents_file = fopen("pastevents.txt", "w");
    if (pastevents_file != NULL)
    {
        fclose(pastevents_file);
    }
    else
    {
        perror("Purge failed");
    }
}

void pastevents_execute(char *home_directory, char *current_directory, char *previous_directory, int input_index, int history_count, int current_command_index, char *history[history_sz], int *ptr_history_count, int *ptr_current_command_index, char *system_command_name, int *ptr_time_taken, ptrnode linkedlist)
{
    if (input_index > history_count)
    {
        perror("Nothing happened that long ago");
        return;
    }
    int i = input_index - 1;
    int j = current_command_index - i;
    // printf("history[j] = %s\n", history[j]);
    char *input_string = strdup(history[j]);

    // printf("input_string = %s\n", input_string);
    // printf("len = %ld\n", strlen(input_string));

    input_function(input_string, home_directory, current_directory, previous_directory, history, history_count, current_command_index, ptr_history_count, ptr_current_command_index, 1, system_command_name, ptr_time_taken, linkedlist);
}
