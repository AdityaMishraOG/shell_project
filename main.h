#ifndef __MAIN_H
#define __MAIN_H

char *create_string();
void update_history(int *current_command_index, int *history_count, char *history[15], char input[4097]);
void restore_history();

#endif