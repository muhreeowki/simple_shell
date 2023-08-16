#include "shell.h"


/* Checks if a program exists or not */
char *find_program(char *name, char **paths)
{
	int i;
	char *filepath;
	struct stat st;

	if (stat(name, &st) == 0)
		return (name);

	/* 2. loop through the list of paths searching for the name */
	for (i = 0; paths[i] != NULL; i++)
	{
		filepath = _strcat(paths[i], _strcat("/", name));

		if (stat(filepath, &st) == 0)
		{
			return (filepath);
		}

		else 
			continue;
	}

	/* 3. Return 0 on succes and -1 on failur. */
	return (NULL);
}




/* function tokenization() - splits command into list of arguments and return list of args */
char **tokenize(char *input, const char delim)
{
	int i, count;
	char **arguments_list;

	/* Count number of tokens */
	count = count_tokens(input, delim);

	/* allocate memory */
	arguments_list = malloc(sizeof(char *) * (count + 1));
	if (arguments_list == NULL)
	{
		perror(NULL);
		return (NULL);
	}

	/* function _strtok() */
	/* get command name */
	arguments_list[0] = strtok(input, &delim);

	/* split the arguments into the string */
	for (i = 1; i < count; i++)
		arguments_list[i] = strtok(NULL, &delim); /* CREATE OUR OWN strtok function */

	return (arguments_list);
}




/* function to count number of tokens in a string */
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


/* funtion to append a command to a linked list of commands */
cmd **append_cmd(cmd **head, char *cmdname, char **arguments)
{
	cmd *new = malloc(sizeof(cmd));

	if (new == NULL)
	{
		perror(NULL);
		return (NULL);
	}

	new->name = cmdname;
	new->arguments = arguments;
	new->next = NULL;

	if (head == NULL || *head == NULL)
		head = &new;
	else
	{
		cmd *curr = *head;

		while (curr->next)
			curr = curr->next;

		curr->next = new;
	}

	return(head);
}

