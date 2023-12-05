#include "headers.h"

void foreground_system_calls(char *phrase, char *system_command_name, int *ptr_time_taken)
{
    // printf("running %s in the foreground\n", phrase);

    char *phrase_copy = strdup(phrase);
    char delims[] = " \t\n\0";
    char *word;
    char *args[sz];
    int i = 0;
    while (word = strtok_r(phrase_copy, delims, &phrase_copy))
    {
        args[i] = strdup(word);
        i++;
    }

    args[i] = NULL;
    // for (int i2 = 0; i2 < i; i2++)
    // {
    //     printf("args[%d] = %s\n", i2, args[i2]);
    // }
    // printf("\n");

    // STARTING TIME
    struct timespec start_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    int fork_ret = fork();
    if (fork_ret < 0)
    {
        perror("Failed to execute system call");
    }

    else if (fork_ret == 0)
    {
        // printf("child process with pid: %d\n", getpid());
        execvp(args[0], args);
        perror("Failed to execute system call");
    }
    else
    {
        // BACK TO PARENT PROCESS
        int child_pid = wait(NULL);
        // ENDING TIME
        struct timespec end_time;
        clock_gettime(CLOCK_MONOTONIC, &end_time);

        double execution_time = (double)(end_time.tv_sec - start_time.tv_sec) + (double)(end_time.tv_nsec - start_time.tv_nsec) / 1000000000.0;
        int floor_integer = (int)execution_time;
        if (floor_integer > 2)
        {
            // ADD IT TO PROMPT
            // system_command_name = strdup(args[0]);
            strcpy(system_command_name, args[0]);
            *ptr_time_taken = floor_integer;
        }
    }
}

void background_system_calls(char *phrase, ptrnode linkedlist)
{
    // printf("running %s in the background\n", phrase);

    char *phrase_copy = strdup(phrase);
    char delims[] = " \t\n\0";
    char *word;
    char *args[sz];
    int i = 0;
    while (word = strtok_r(phrase_copy, delims, &phrase_copy))
    {
        args[i] = strdup(word);
        i++;
    }

    args[i] = NULL;

    int fork_ret = fork();
    if (fork_ret < 0)
    {
        perror("Failed to execute system call");
    }

    else if (fork_ret == 0)
    {
        // printf("child process with pid: %d\n", getpid());
        execvp(args[0], args);
        // printf("Failed to execute system call");
    }
    else
    {
        // BACK TO PARENT PROCESS

        printf("%d\n", fork_ret);
        linkedlist = insertnode(linkedlist, fork_ret, phrase);
        return;
    }
}
