#include "shell.h"

/**
 * tokenize - divides a string input into a list of tokens/words
 * (similar to _strtok)
 *
 * @input: pointer to string
 * @delim: delimiter to divide the string by
 *
 * Return: Pointer to list of string
 */
char **tokenize(char *input, const char delim)
{
	int i, count, n = 0, flag = 1, start = 0;
	char **arguments_list, *substring, *string = _strdup(input);
	
	count = count_tokens(string, delim);
	arguments_list = malloc(sizeof(char *) * (count + 1));
	if (arguments_list == NULL)
	{
		perror(NULL);
		return (NULL);
	}

	/* Divide this function into parts */
	/* One part to handle delimiter and another part to handle quotes */
	for (i = 0; string[i] != '\0'; i++)
	{
		if (flag == 1)
		{
			start = i;
			substring = (string + start);
			flag = 0;
			/*
			if (*substring == '"')
			{
				substring++;
				while(string[i] != '"')
					i++;
				string[i] = '\0';
				printf("%s\n", substring);
				arguments_list[n++] = substring;
				flag = 1;
				continue;
			}
			else
				flag = 0;
			*/
		}
		if (string[i] == delim)
		{
			string[i] = '\0';
			flag = 1;
			if (string[i - 1] > 32 && string[i - 1] < 127)
			{
				arguments_list[n++] = substring;
				printf("%s\n", substring);
			}
		}
	}

	if (string[i - 1] > 32 && string[i - 1] < 127)
		arguments_list[n] = substring;

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
