#include "shell.h"

/**
 * tokenize - divides a string input into a list of tokens/words
 *
 * @input: pointer to string
 * @delim: delimiter to divide the string by
 *
 * Return: Pointer to list of string
 */
char **tokenize(char *input, const char delim)
{
	int i, count;
	char **arguments_list;
	char *string = _strdup(input);

	/* Count number of tokens */
	count = count_tokens(string, delim);

	/* allocate memory */
	arguments_list = malloc(sizeof(char *) * (count + 1));
	if (arguments_list == NULL)
	{
		perror(NULL);
		return (NULL);
	}

	/* get command name */
	arguments_list[0] = strtok(string, &delim);

	/* split the arguments into the string */
	for (i = 1; i <= count; i++)
	{
		arguments_list[i] = strtok(NULL, &delim);
	}

	return (arguments_list);
}


/**
 * count_tokens - counts the number of tokens/words in a string
 *
 * @input: pointer to string
 * @delim: delimiter to divide the string by
 *
 * Return: Pointer to list of string
 */
int count_tokens(char *input, char delim)
{
	int i, count = 1;

	for (i = 0; input[i] != '\0'; i++)
	{
		if (input[i] == delim)
			count++;
	}

	return (count);
}


/**
 * append_cmd - appends a command to a linked list of commands
 *
 * @head: pointer to head of list
 * @cmdname: name of command
 * @arguments: pointer to a list of arguments strings
 * @sep: pointer to the separator
 *
 * Return: Pointer to head of list
 */
cmd *append_cmd(cmd *head, char *cmdname, char **arguments, char *sep)
{
	cmd *new = malloc(sizeof(cmd)), *curr = head;

	if (new == NULL)
	{
		perror(NULL);
		return (NULL);
	}

	new->builtin = -1;
	new->name = cmdname;
	new->arguments = arguments;
	new->separator = sep;
	new->function = NULL;
	new->next = NULL;

	if (head == NULL)
		return (new);

	while (curr->next)
		curr = curr->next;

	curr->next = new;

	return (head);
}
