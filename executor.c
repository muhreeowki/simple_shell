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
int executor(cmd *head, char **paths, char *name, int *count, int *exit_status)
{
	int curr_status = 0, prev_status = 0;
	cmd *command = head;
	cmd raw_command;
	char *curr_sep = NULL, *prev_sep = NULL, *msg,
	     *errmsg[15] = {NULL, NULL, ": ", NULL, ": not found\n", NULL};

	errmsg[0] = name;

	while (command != NULL)
	{
		prev_sep = curr_sep;
		curr_sep = command->separator;

		switch (check_sep(prev_sep, curr_status, prev_status))
		{
		case -1:
			return(curr_status);
		case 1:
			command = command->next;
			continue;
		}

		if (!find_program(command, paths)) /* Find the program */
		{
			errmsg[1] = _itoa(*count, 10);
			errmsg[3] = command->name;
			msg = _strcat2(errmsg);
			free(errmsg[1]);
			write(STDERR_FILENO, msg, _strlen(msg));
			free(msg);
			curr_status = 127;
		}

		if (command->builtin == 0) /* Execute a builtin */
		{
			raw_command = *command;
			curr_status = raw_command.function(command->arguments, name, count, exit_status);
		}

		if (command->builtin > 0) /* Execute Program via exec */
			execute_command(command, &curr_status, &prev_status);

		command = command->next;
		(*count)++;
	}
	return (curr_status);
}
