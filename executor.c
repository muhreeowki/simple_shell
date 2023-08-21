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
void executor(cmd *head, char **paths)
{
	int curr_status = 0, prev_status = 0;
	cmd *command = head;
	cmd raw_command;
	char *curr_sep = NULL, *prev_sep = NULL, *errmsg;

	while (command != NULL)
	{
		prev_sep = curr_sep;
		curr_sep = command->separator;

		switch (check_sep(prev_sep, curr_status, prev_status))
		{
		case -1:
			return;
		case 1:
			command = command->next;
			continue;
		}

		if (!find_program(command, paths)) /* Find the program */
		{
			errmsg = _strcat(program_name ,_strcat(command->name, ": not found\n"));
			write(STDERR_FILENO, errmsg, _strlen(errmsg));
			curr_status = -1;
		}
			

		if (command->builtin == 0) /* Execute a builtin */
		{
			raw_command = *command;
			curr_status = raw_command.function(command->arguments);
		}

		if (command->builtin == 1) /* Execute Program via exec */
			execute_command(command, &curr_status, &prev_status);

		command = command->next;
		command_count++;
	}
}
