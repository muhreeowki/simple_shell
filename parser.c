#include "shell.h"

cmd **parser(char *input, char **paths)
{
	char **arguments_list;
	int i = 0, count = 1;
	cmd *new_cmd;
	cmd **head = NULL;

	/* function tokenization() - splits command into list of arguments and return list of args */
	arguments_list = tokenize();

	/* TODO: Check for seperators and logical opperators and append them to the seperators list */
	/* TODO: if seperators are found, Repeat until we find all the commands. */

	/* function find_program() */
	/* check if program exists */

	if (find_program(arguments_list[0]) == -1)
	{
		perror(NULL);
		return (NULL);
	}


	/* Initialization of command */
	/* function append_node() */
	new_cmd = malloc(sizeof(cmd));
	if (new_cmd == NULL)
	{
		perror(NULL);
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
