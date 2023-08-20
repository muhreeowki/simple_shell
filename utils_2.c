#include "shell.h"

/**
 * free_cmdlist - frees a linked list
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

int _strlen(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
		;

	return (len);
}

int handle_errors(char *message)
{
	perror(message);
	return (-1);
}

/**
 * _atoi - converts a string to an int
 *
 * @s: Pointer to string to converted
 *
 * Return: dest
 */
int _atoi(char *s)
{
	int i, j, num, length, test_int = 1;
	unsigned int value = 0;

	length = _strlen(s);

	for (i = 0; i < length; i++)
	{
		if (*(s + i) >= 48 && *(s + i) <= 57)
		{
			while (*(s + i) >= 48 && *(s + i) <= 57)
			{
				num = *(s + i);
				value = value * 10 + (num - 48);
				i++;
			}
			break;
		}
	}

	if (value == 0)
		return (0);

	for (j = 0; j < i; j++)
	{
		if (*(s + j) == '-')
			test_int = -test_int;
		if (*(s + j) == '+')
			test_int = +test_int;
	}

	if (test_int == -1)
		return (-value);

	return (value);
}
