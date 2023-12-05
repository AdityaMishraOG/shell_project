#include "headers.h"

void printlinkedlist(ptrnode linkedlist)
{
    ptrnode cur = linkedlist->next;
    while (cur != NULL)
    {
        printf("pid: %d, %s\n", cur->pid, cur->name);
        cur = cur->next;
    }
}

ptrnode createnode(int input_pid, char *input_name)
{
    ptrnode ret = (ptrnode)malloc(sizeof(struct node));
    ret->pid = input_pid;
    ret->name = (char *)calloc(sz, sizeof(char));
    strcpy(ret->name, input_name);
    ret->next = NULL;
    return ret;
}
ptrnode insertnode(ptrnode linkedlist, int inp_pid, char *inp_name)
{
    ptrnode new_node = createnode(inp_pid, inp_name);
    new_node->next = linkedlist->next;
    linkedlist->next = new_node;
    return linkedlist;
}

ptrnode deletenode(ptrnode linkedlist)
{
    ptrnode cur = linkedlist->next;
    ptrnode prev = linkedlist;

    int process_status;
    int completion_check;

    while ((completion_check = waitpid(-1, &process_status, WNOHANG)) > 0)
    {
        while (cur != NULL)
        {
            int cur_pid = cur->pid;

            // PROCESS COMPLETED
            if (completion_check == cur_pid)
            {

                // SUCCESSFUL
                if (WIFEXITED(process_status))
                {
                    printf("%s with pid %d exited normally \n", cur->name, cur_pid);
                }
                else
                {
                    printf("%s did not exit normally: ", cur->name);
                    perror("exit issue");
                }
                prev->next = cur->next;
                free(cur);

                // prev = prev->next;
                cur = prev->next;
            }
        }
    }
}
