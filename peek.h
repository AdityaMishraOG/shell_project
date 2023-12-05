#ifndef __PEEK_H
#define __PEEK_H

int alphasort(const struct dirent **entry1, const struct dirent **entry2);
void print_file_permissions(mode_t mode);
void peek(char *path_string, char *home_directory, char *current_directory, char *previous_directory, int a, int l);

#endif