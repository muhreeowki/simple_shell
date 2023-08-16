#include "shell.h"

cmd **parser(char *input, char **paths)
{
	char **arguments_list;
	cmd **head = NULL;
	char *cmd_name;	

	/* function tokenization() - splits command into list of arguments and return list of args */
	arguments_list = tokenize(input, ' ');

	/* TODO: Check for seperators and logical opperators and append them to the seperators list */
	/* TODO: if seperators are found, Repeat until we find all the commands. */

	/* function find_program() */
	/* check if program exists */

	/* find_program(arguments_list[0], paths); */


	cmd_name = find_program(arguments_list[0], paths);
	if (cmd_name == NULL)
		return (NULL);


	/* Initialization of command */
	/* function append_node() */
	/* Append command to commands list */
	arguments_list[0] = cmd_name;
	append_cmd(head, arguments_list[0], arguments_list);

	/*
	new_cmd = malloc(sizeof(cmd));
	if (new_cmd == NULL)
	{
		perror(NULL);
		TODO: Free the arguments list 
		return (NULL);
	}
	new_cmd->name = arguments_list[0];
	new_cmd->arguments = arguments_list;
	new_cmd->next = NULL;

	head = &new_cmd;
	*/

	printf("parser done\n");

	return (head);
}
