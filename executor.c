#include "shell.h"

void executor(cmd *head, char **paths)
{
	int status;
	char *separator;
	cmd *curr = head;

	while(curr != NULL)
	{
		find_program(*curr, paths);
		if (curr->builtin == 0)
		{
			curr->function(curr->arguments);
			return;
		}

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
