#include "shell.h"
#include <stdio.h>
/**
 
print_listint - Prints integer elements of a listint_t list.
@h: Pointer to the head of the list.
Return: Number of nodes in the list.
*/

void print_cmd(cmd *head)
{
    int i = 0;
    cmd *curr = head;

    while (curr)
    {
        printf("command name: %s\n", curr->name);
	while (curr->name[i] != '\0')
		i++;
	printf("name length: %d\n", i);

        printf("separator: %s\n", curr->separator);

	for (i = 0; curr->arguments[i] != NULL; i++)
        	printf("arg[%d]: %s\n", i, curr->arguments[i]);

        curr = curr->next;
	printf("\n");
    }
}
