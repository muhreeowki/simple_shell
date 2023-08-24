#include "shell.h"

/**
 * executor - Executes a list of commands.
 * @head: Pointer to command list.
 * @paths: List of paths in PATH env variable.
 * @name: Name of the program executing commands.
 * @count: Pointer to command count.
 * @exit_status: Pointer to exit status.
 * Return: Exit status of the last command executed.
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
			return (curr_status);
		case 1:
			command = command->next;
			continue;
		}
		if (!find_program(command, paths))
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
			curr_status = raw_command.function(command->arguments,
					name, count, exit_status);
		}
		if (command->builtin > 0) /* Execute Program via exec */
			execute_command(command, &curr_status, &prev_status);
		command = command->next;
		(*count)++;
	}
	return (curr_status);
}
