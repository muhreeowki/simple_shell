#include "shell.h"
#include <stdio.h>
/**
 
print_listint - Prints integer elements of a listint_t list.
@h: Pointer to the head of the list.
Return: Number of nodes in the list.
*/

void print_cmd(cmd *head)
{
    int i;
    cmd *curr = head;

    while (curr)
    {
        printf("name: %s\n", curr->name);

	for (i = 0; curr->arguments[i] != NULL; i++)
        	printf("arg[%d]: %s\n", i, curr->arguments[i]);

        curr = curr->next;
    }
    printf("\n");
}
