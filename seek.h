#ifndef __SEEK_H
#define __SEEK_H

void seek_util(int d, int e, int f, char *search, char *target_location, char *home_directory, char *current_directory, char *outermost_target_location, int *match_found_files, int *match_found_directories);

char *seek_e_flag(int d, int e, int f, char *search, char *target_location, char *home_directory, char *current_directory, char *outermost_target_location);

void seek(int d, int e, int f, char *search, char *target_directory, char *home_directory, char *current_directory);

#endif