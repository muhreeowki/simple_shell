#include "shell.h"

cmd **parser(char *input)
{
	char **arguments_list;
	int i = 0, count = 1;
	cmd *new_cmd;
	cmd **head = NULL;

	/* function tokenization() - splits command into list of arguments and return list of args */

	/* function count_args() */
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
		perror(NULL);
		return (NULL);
	}

	/* function _strtok() */
	/* get command name */
	arguments_list[0] = strtok(input, " ");

	/* split the arguments into the string */
	for (i = 1; i <= count; i++)
	{
		arguments_list[i] = strtok(NULL, " ");

	}

	/* TODO: Check for seperators and logical opperators and append them to the seperators list */
	/* TODO: if seperators are found, Repeat until we find all the commands. */

	/* function find_program() */
	/* check if program exists 

	if (find_program(arguments_list[0]))

	*/

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
