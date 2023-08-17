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

	if (head == NULL)
		return;

	while (ptr)
	{
		next = ptr->next;
		free(ptr->arguments);
		free(ptr);
		ptr = next;
	}
}
