#ifndef __SYSTEM_CALLS_H
#define __SYSTEM_CALLS_H

void foreground_system_calls(char *phrase, char *system_command_name, int *ptr_time_taken);
void background_system_calls(char *phrase, ptrnode linkedlist);

#endif