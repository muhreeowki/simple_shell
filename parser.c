#include "shell.h"

/* TODO: Check for seperators and logical opperators and append them to the seperators list */
/* TODO: if seperators are found, Repeat until we find all the commands. */

cmd *parser(char *input, char **paths)
{
	char **arguments_list;
	cmd *head = NULL;
	char *cmd_name;	

	/* function tokenization() - splits command into list of arguments and return list of args */
	arguments_list = tokenize(input, ' ');

	/* check if program exists */
	cmd_name = find_program(arguments_list[0], paths);
	if (cmd_name == NULL)
		return (NULL);

	/* Append command to commands list */
	arguments_list[0] = cmd_name;
	head = append_cmd(head, arguments_list[0], arguments_list);

	return (head);
}
