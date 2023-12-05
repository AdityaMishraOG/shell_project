#ifndef __PASTEVENTS_H
#define __PASTEVENTS_H
#include "headers.h"

void pastevents(int history_count, int current_command_index, char *history[15]);
void pastevents_purge(int *ptr_history_count, int *ptr_current_command_index);
void pastevents_execute(char *home_directory, char *current_directory, char *previous_directory, int input_index, int history_count, int current_command_index, char *history[15], int *ptr_history_count, int *ptr_current_command_index, char *system_command_name, int *ptr_time_taken, ptrnode linkedlist);

#endif