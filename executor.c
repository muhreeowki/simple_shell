#include "shell.h"

/**
 * executor - function to handle execution of
 * all the commands in a list
 *
 * @head: pointer to a list of commands
 * @paths: list of all the paths in the PATH
 * environmental variable
 *
 * Return: nothing.
 */
int executor(cmd *head, char **paths, char *name, int *count)
{
	int curr_status = 0, prev_status = 0;
	cmd *command = head;
	cmd raw_command;
	char *curr_sep = NULL, *prev_sep = NULL, *msg, *msg_pt1, *msg_pt2;

	while (command != NULL)
	{
		if (!find_program(command, paths)) /* Find the program */
		{
			msg_pt1 = _strcat(name, _strcat(_itoa(*count, 10), ": "));
			msg_pt2 = _strcat(command->name, ": not found\n");
			msg = _strcat(msg_pt1, msg_pt2);
			write(STDERR_FILENO, msg, _strlen(msg));
			curr_status = 127;
		}

		if (command->builtin == 0) /* Execute a builtin */
		{
			raw_command = *command;
			curr_status = raw_command.function(command->arguments, name, count);
		}

		if (command->builtin == 1) /* Execute Program via exec */
			execute_command(command, &curr_status, &prev_status);

		prev_sep = curr_sep;
		curr_sep = command->separator;

		switch (check_sep(prev_sep, curr_sep, curr_status, prev_status))
		{
		case -1:
			return(curr_status);
		case 1:
			command = command->next;
			continue;
		}

		command = command->next;
		(*count)++;
	}
	return (curr_status);
}
