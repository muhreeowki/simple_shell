#include "shell.h"

/* function tokenization() - splits command into list of arguments and return list of args */
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
		arguments_list[i] = strtok(NULL, &delim); /* CREATE OUR OWN strtok function */
	}

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
cmd *append_cmd(cmd *head, char *cmdname, char **arguments, char *sep)
{
	cmd *new = malloc(sizeof(cmd));

	if (new == NULL)
	{
		perror(NULL);
		return (NULL);
	}

	new->name = cmdname;
	new->arguments = arguments;
	new->separator = sep;
	new->next = NULL;

	if (head == NULL)
		return (new);
	else
	{
		cmd *curr = head;

		while (curr->next)
			curr = curr->next;

		curr->next = new;

		return(head);
	}

}
