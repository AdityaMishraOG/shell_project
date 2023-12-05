#include "headers.h"
#include "linked_list.h"

void input_function(char *input_string, char *home_directory, char *current_directory, char *previous_directory, char *history[sz], int history_count, int current_command_index, int *ptr_history_count, int *ptr_current_command_index, int coming_from_pastevents_execute_flag, char *system_command_name, int *time_taken, ptrnode linkedlist)
{
    if (coming_from_pastevents_execute_flag == 1)
    {
        if (strcmp(history[current_command_index], input_string) != 0)
        {
            update_history(ptr_current_command_index, ptr_history_count, history, input_string);
        }
    }
    char *command = strtok_r(input_string, ";", &input_string);

    while (command)
    {
        int number_of_ampersands = 0;
        for (int i = 0; i < strlen(command); i++)
        {
            if (command[i] == '&')
                number_of_ampersands++;
        }

        char *phrase = strtok_r(command, "&", &command);
        char *previous_phrase = NULL;
        // printf("number of ampersands = %d\n", number_of_ampersands);
        int count_of_phrases = 0;

        int system_call_flag = 0;
        while (phrase)
        {
            count_of_phrases++;
            // WARP FLAGS
            int warp_blank_input = 1;
            // PEEK FLAGS
            int l = 0, a = 0, peek_blank_input = 1;
            // PROCLORE FLAGS
            int proclore_blank_input = 1;
            // SEEK FLAGS
            int d = 0, e = 0, f = 0, search_flag = 0, target_flag = 0;
            char *search_term;
            char *target_directory;
            // PASTEVENTS FLAGS
            int pastevents_blank_input = 1;

            // RUNNING IN THE BACKGROUND
            if (previous_phrase != NULL && system_call_flag)
            {
                // printf("run %s in the background line 48\n", previous_phrase);
                background_system_calls(previous_phrase, linkedlist);
                system_call_flag = 0;
            }

            // printf("phrase = %s\n", phrase);
            char *phrase_copy = strdup(phrase);

            // DEALING WITH EACH WORD
            char delims[] = " \t\n\0";
            char *word = strtok_r(phrase_copy, delims, &phrase_copy);
            int instruction_flag = 0;

            // warp -> 1
            // peek -> 2
            // proclore -> 3
            // pastevents -> 4
            // seek -> 5
            // exit -> 6 (no flag necessary)
            // system commands -> 7 (else condition)
            if (strcmp(word, "warp") == 0)
            {
                instruction_flag = 1;
                word = strtok_r(phrase_copy, delims, &phrase_copy);
            }
            else if (strcmp(word, "peek") == 0)
            {
                instruction_flag = 2;
                word = strtok_r(phrase_copy, delims, &phrase_copy);
            }
            else if (strcmp(word, "proclore") == 0)
            {
                instruction_flag = 3;
                word = strtok_r(phrase_copy, delims, &phrase_copy);
            }
            else if (strcmp(word, "pastevents") == 0)
            {
                instruction_flag = 4;
                word = strtok_r(phrase_copy, delims, &phrase_copy);
            }
            else if (strcmp(word, "seek") == 0)
            {
                instruction_flag = 5;
                word = strtok_r(phrase_copy, delims, &phrase_copy);
            }
            else if (strcmp(word, "exit") == 0)
            {
                exit_function(history, history_count, current_command_index);
            }
            else
            {
                system_call_flag = 1;
            }

            while (word)
            {
                // printf("word = %s\n", word);
                if (instruction_flag == 1)
                {
                    // warp
                    warp(word, home_directory, current_directory, previous_directory);
                    warp_blank_input = 0;
                }
                else if (instruction_flag == 2)
                {
                    // peek
                    if (strcmp(word, "-l") == 0)
                    {
                        l = 1;
                    }
                    else if (strcmp(word, "-a") == 0)
                    {
                        a = 1;
                    }
                    else if (strcmp(word, "-la") == 0)
                    {
                        l = 1;
                        a = 1;
                    }
                    else if (strcmp(word, "-al") == 0)
                    {
                        l = 1;
                        a = 1;
                    }
                    else
                    {
                        peek(word, home_directory, current_directory, previous_directory, a, l);
                        a = 0, l = 0, peek_blank_input = 0;
                    }
                }
                else if (instruction_flag == 3)
                {
                    // proclore
                    int pid = atoi(word);
                    proclore(home_directory, pid);
                    proclore_blank_input = 0;
                }
                else if (instruction_flag == 4)
                {
                    // pastevents
                    if (strcmp(word, "purge") == 0)
                    {
                        pastevents_purge(ptr_history_count, ptr_current_command_index);
                        pastevents_blank_input = 0;
                    }
                    else if (strcmp(word, "execute") == 0)
                    {
                        word = strtok_r(phrase_copy, delims, &phrase_copy);
                        int input_index = atoi(word);
                        pastevents_execute(home_directory, current_directory, previous_directory, input_index, history_count, current_command_index, history, ptr_history_count, ptr_current_command_index, system_command_name, time_taken, linkedlist);
                        pastevents_blank_input = 0;
                    }
                }
                else if (instruction_flag == 5)
                {
                    // seek
                    if (strcmp(word, "-d") == 0)
                    {
                        d = 1;
                    }
                    else if (strcmp(word, "-e") == 0)
                    {
                        e = 1;
                    }
                    else if (strcmp(word, "-f") == 0)
                    {
                        f = 1;
                    }
                    else
                    {
                        if (search_flag == 0)
                        {
                            search_term = strdup(word);
                            search_flag = 1;
                        }
                        else if (search_flag && target_flag == 0)
                        {
                            target_directory = strdup(word);
                            // printf("running seek for d = %d, e = %d, f = %d\n", d, e, f);
                            // printf("searching %s in %s\n", search_term, target_directory);
                            if (d && f)
                            {
                                perror("Invalid flags!");
                                return;
                            }
                            seek(d, e, f, search_term, target_directory, home_directory, current_directory);
                            target_flag = 1;
                        }
                    }
                }
                word = strtok_r(phrase_copy, delims, &phrase_copy);
            }
            // WARP WHEN NO PATH IS GIVEN
            if (word == NULL && instruction_flag == 1 && warp_blank_input)
            {
                warp("~", home_directory, current_directory, previous_directory);
            }
            // PEEK WHEN NO PATH IS GIVEN
            if (word == NULL && instruction_flag == 2 && peek_blank_input)
            {
                peek(".", home_directory, current_directory, previous_directory, a, l);
            }
            // PROCLORE WHEN NO PID IS GIVEN
            if (word == NULL && instruction_flag == 3 && proclore_blank_input)
            {
                proclore(home_directory, -1);
            }
            // PASTEVENTS WHEN NO ARGUMENT IS GIVEN
            if (word == NULL && instruction_flag == 4 && pastevents_blank_input)
            {
                pastevents(history_count, current_command_index, history);
            }
            // SEEK WHEN NO TARGET DIRECTORY IS GIVEN
            if (word == NULL && search_flag == 1 && target_flag == 0)
            {
                if (d && f)
                {
                    perror("Invalid flags!");
                    return;
                }
                seek(d, e, f, search_term, current_directory, home_directory, current_directory);
            }
            // DEALT WITH EACH WORD

            previous_phrase = strdup(phrase);
            // run_prev_in_background = 1;
            phrase = strtok_r(command, "&", &command);
        }
        // RUNNING IN THE BACKGROUND
        if (previous_phrase != NULL && number_of_ampersands == count_of_phrases && system_call_flag)
        {
            // printf("run %s in the background line 234\n", previous_phrase);
            background_system_calls(previous_phrase, linkedlist);
            system_call_flag = 0;
        }
        // RUNNING IN THE FOREGROUND
        else if (previous_phrase != NULL && system_call_flag)
        {
            // printf("run %s in the foreground line 241\n", previous_phrase);
            // printf("pid = %d\n", getpid());
            foreground_system_calls(previous_phrase, system_command_name, time_taken);
            system_call_flag = 0;
        }
        command = strtok_r(input_string, ";", &input_string);
        // printf("count_of_phrases = %d\n", count_of_phrases);
        // printf("number_of_ampersands = %d\n", number_of_ampersands);
    }
}