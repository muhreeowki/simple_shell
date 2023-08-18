#include "shell.h"

/**
 * find_program - searches through the PATH to find
 * a program by name or filepath
 *
 * @command: a command.
 * @paths: exit status of most previous command.
 *
 * Return: command.
 */
cmd *find_program(cmd *command, char **paths)
{
	int i;
	char *filepath;
	struct stat st;
	cmd builtins[] = {
		{0, "cd", NULL, NULL, _cd, NULL}, {0, "env", NULL, NULL, _env, NULL},
		{0, "setenv", NULL, NULL, NULL, NULL},
		{0, "unsetenv", NULL, NULL, NULL, NULL},
		{0, "exit", NULL, NULL, NULL, NULL}, {0, "alias", NULL, NULL, NULL, NULL},
		{0, NULL, NULL, NULL, NULL, NULL},
	};

	for (i = 0; builtins[i].name != NULL; i++)
	{
		if (_strcmp(builtins[i].name, command->name) == 0)
		{
			command->builtin = 0;
			command->function = builtins[i].function;
			return (command);
		}
	}

	if (stat(command->name, &st) == 0)
	{
		command->builtin = 1;
		return (command);
	}

	for (i = 0; paths[i] != NULL; i++)
	{
		filepath = _strcat(paths[i], _strcat("/", command->name));

		if (stat(filepath, &st) == 0)
		{
			command->name = filepath;
			command->builtin = 1;
			return (command);
		}
	}
	
	return (NULL);
}

/**
 * check_sep - Handles command separators and logical separators
 *
 * @sep: a separator
 * @curr_state: exit status of most recent command
 * @prev_state: exit status of most previous command
 *
 * Description: This function returns a number based on afew conditions.
 * 1. If sep is ; or NULL then we execute the next command.
 *
 * 2. If sep is || then we check the status of the previous command's
 * exit status. If the status is 0 (success) we skip the next command,
 * otherwise we execute the next command.
 *
 * 3. If sep is &&, we check the exit status for the previous command,
 * if it is 0 we continue, if it isn't we terminate.
 *
 * Return:
 * 0 -> Continue to next command
 * 1 -> Skip the next command
 * -1 -> Terminate: Do not run the next command.
 */
int check_sep(char *sep, int curr_state, int prev_state)
{
	if (sep == NULL || sep[0] == ';')
		return (0);

	if ((sep[0] == '&' && sep[1] == '&'))
		if (prev_state == 0 && curr_state == 0)
			return (0);

	if ((sep[0] == '|' && sep[1] == '|'))
	{
		if (curr_state == 0)
			return (1);
		return (0);
	}

	return (-1);
}

/**
 * execute_command - Execute a command inside a child proccess.
 *
 * @command: a command.
 * @curr_state: exit status of most recent command.
 * @prev_state: exit status of most previous command.
 *
 * Return: nothin.
 */

void execute_command(cmd *command, int *curr_state, int *prev_state)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror(NULL);
		return;
	}
	if (pid == 0)
	{
		execve(command->name, command->arguments, environ);
		perror(NULL);
	}
	else
	{
		*prev_state = *curr_state;
		wait(curr_state);
	}
}
