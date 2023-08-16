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
    cmd *h = head;

    while (h != NULL)
    {
        printf("name: %s\n", h->name);

	for (i = 0; h->arguments[i] != NULL; i++)
        	printf("arg[%d]: %s\n\n", i, h->name);

        h = h->next;
    }

}
