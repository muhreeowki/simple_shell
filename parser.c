#include "shell.h"

cmd **parser(char *input)
{
	char **arguments_list;
	int i = 0, count = 1;
	cmd *new_cmd;
	cmd **head = NULL;

	/* Tokenization */

	/* count args */
	while (input[i] != '\0')
	{
		if (input[i] == ' ')
			count++;
		i++;
	}

	/* 3 */
	arguments_list = malloc(sizeof(char *) * (count + 1));
	if (arguments_list == NULL)
	{
		perror("Memory allocation error\n");
		return (NULL);
	}

	/* get command name */
	arguments_list[0] = strtok(input, " ");

	/* split the arguments into the string */
	for (i = 1; i <= count; i++)
	{
		arguments_list[i] = strtok(NULL, " ");

		/* TODO: Check for seperators and logical opperators and append them to the seperators list */
		/* TODO: if seperators are found, Repeat until we find all the commands. */
	}


	/* Initialization of command */
	new_cmd = malloc(sizeof(cmd));
	if (new_cmd == NULL)
	{
		perror("Memory allocation error\n");
		/* TODO: Free the arguments list */
		return (NULL);
	}
	new_cmd->name = arguments_list[0];
	new_cmd->arguments = arguments_list;
	new_cmd->next = NULL;

	/* Append command to commands list */
	head = &new_cmd;

	return (head);
}
