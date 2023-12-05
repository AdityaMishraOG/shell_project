#ifndef __INPUT_H
#define __INPUT_H

#include "linked_list.h"

void input_function(char *input_string, char *home_directory, char *current_directory, char *previous_directory, char *history[15], int history_count, int current_command_index, int *ptr_history_count, int *ptr_current_command_index, int coming_from_pastevents_execute_flag, char *system_command_name, int *time_taken, ptrnode linkedlist);

#endif