#ifndef __LINKED_LIST_H
#define __LINKED_LIST_H
#include "headers.h"

struct node
{
    int pid;
    char *name;
    struct node *next;
};
typedef struct node *ptrnode;

void printlinkedlist(ptrnode linkedlist);
ptrnode createnode(int input_pid, char *input_name);
ptrnode insertnode(ptrnode linkedlist, int inp_pid, char *inp_name);
ptrnode deletenode(ptrnode linkedlist);

#endif