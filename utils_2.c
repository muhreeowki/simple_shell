#include "shell.h"

/**
 * free_listint - frees a linked list
 *
 * @head: pointer to the head of the linked list
 *
 * Return: nothing.
 */
void free_cmdlist(cmd *head)
{
	cmd *ptr = head;
	cmd *next;

	if (ptr == NULL)
		return;

	free(ptr->arguments);

	while (ptr)
	{
		next = ptr->next;
		free(ptr);
		ptr = next;
	}
}
