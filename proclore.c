#include "headers.h"

void proclore(char *home_directory, int user_input_pid)
{
    int process_id = getpid();
    char process_status;
    int foreground_flag;
    int process_group;
    int terminal_process_group;
    int virtual_memory;
    char *relative_executable_path = (char *)calloc(sz, sizeof(char));

    if (user_input_pid != -1)
        process_id = user_input_pid;

    // READING /proc/[pid]/stat
    char stat_location[sz];
    snprintf(stat_location, sz, "/proc/%d/stat", process_id);

    int stat_fd = open(stat_location, O_RDONLY);
    if (stat_fd != -1)
    {
        char *stat_content = (char *)calloc(sz, sizeof(char));
        int bytes_read = read(stat_fd, stat_content, sz);
        stat_content[bytes_read] = '\0';

        char *delimeters = " ";
        char *str = strtok_r(stat_content, delimeters, &stat_content);

        int index = 0;

        // 2 -> process status
        // 4 -> process_group
        // 7 -> terminal_process_group
        // 22 -> virtual memory
        while (str)
        {
            // printf("%s\n", str);

            if (index == 2)
            {
                process_status = str[0];
            }
            if (index == 4)
            {
                process_group = atoi(str);
            }
            if (index == 7)
            {
                terminal_process_group = atoi(str);
            }
            if (index == 22)
            {
                virtual_memory = atoi(str);
            }

            str = strtok_r(stat_content, delimeters, &stat_content);
            index++;
        }
    }
    else
    {
        perror("process with input Process ID not found");
        return;
    }
    // STAT DONE

    // READING /proc/[pid]/exe FILE
    char exe_location[sz];
    snprintf(exe_location, sz, "/proc/%d/exe", process_id);

    int exe_fd = open(exe_location, O_RDONLY);
    if (exe_fd != -1)
    {
        char *exe_content = (char *)calloc(sz, sizeof(char));
        int bytes_read = readlink(exe_location, exe_content, sz);
        exe_content[bytes_read] = '\0';
        // CONVERTING ABSOLUTE EXECUTABLE PATH TO RELATIVE PATH
        relative_executable_path = relative_path(home_directory, exe_content);
    }
    else
    {
        perror("Process with input Process ID not found");
        return;
    }
    // EXE DONE
    // SETTING FOREGROUND FLAG
    foreground_flag = (process_group == terminal_process_group); // PROCESS IS RUNNING IN THE FOREGROUND IFF TPGID == PGID

    // PRINTING THE VALUES
    printf("pid : %d\n", process_id);
    printf("Process Status : %c", process_status);
    if (foreground_flag == 1)
        printf("+");
    printf("\nProcess group : %d\n", process_group);
    printf("Virtual memory : %d\n", virtual_memory);
    printf("executable path : %s\n", relative_executable_path);
}