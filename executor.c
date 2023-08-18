#include "shell.h"

/* List of builtin commands */
/* Add the function pointers to this list of functions */

cmd builtins[] = {
	{0, "cd", NULL, NULL, NULL, NULL},
	{0, "env", NULL, NULL, NULL, NULL},
	{0, "setenv", NULL, NULL, NULL, NULL},
	{0, "unsetenv", NULL, NULL, NULL, NULL},
	{0, "exit", NULL, NULL, NULL, NULL},
	{0, "alias", NULL, NULL, NULL, NULL},
	{0, NULL, NULL, NULL, NULL, NULL},
};

void executor(cmd *head, char **paths)
{
	int curr_status = 0, prev_status = 0;
	cmd *curr = head;
	char *curr_sep = NULL, *prev_sep = NULL;
	pid_t pid;

	while(curr != NULL)
	{
		prev_sep = curr_sep;
		curr_sep = curr->separator;
		/* Check if next command should be ran or not based on separator */
		switch (check_sep(prev_sep, curr_status, prev_status))
		{
		case -1:
			exit(-1);
		case 1:
			curr = curr->next;
			continue;
		}

		/* Find the program */
		if (!find_program(curr, paths))
			perror(NULL);

		/* Update separator */

		/* Execute builtin if function is builtin 
		if (curr->builtin == 0)
			curr->function(curr->arguments);
		 */


		/* Execute Program via exec */
		if (curr->builtin == 1)
		{
			pid = fork();

			if (pid == -1)
			{
				perror(NULL);
				return;
			}
			else if (pid == 0)
			{
				execve(curr->name, curr->arguments, environ);
				perror("execve");
			}
			else
			{
				prev_status = curr_status;
				wait(&curr_status);

			}
		}

		curr = curr->next;
	}
}


/* This function helps us know when to continue to the next command and when to exit */
int check_sep(char *sep, int curr_state, int prev_state)
{
	if (sep == NULL || sep[0] == ';')
		return (0); /* Continue to next command */

	if ((sep[0] == '&' && sep[1] == '&'))
		if (prev_state == 0 && curr_state == 0)
			return (0); /* Continue to next command */

	if ((sep[0] == '|' && sep[1] == '|'))
	{
		if (curr_state == 0)
			return (1); /* Skip the next command */
		return (0); /* Go to next command */
	}

	return (-1); /* Terminate */
}





/* TODO: Add multiple executor sub functions to handle different separators and logicall operations */

/* function to execute a list of commands */
/*
void executor(cmd *head)
{
	int status;
	cmd *curr = head;

	while(curr != NULL)
	{
		pid_t pid = fork();

		if (pid < 0)
		{
			perror(NULL);
			return;
		}
		else if (pid == 0)
		{
			execve(curr->name, curr->arguments, environ);
			perror("execve");
			return;
		}
		else
			wait(&status);

		curr = curr->next;
	}
}
*/
