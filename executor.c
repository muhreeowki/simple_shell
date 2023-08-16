#include "shell.h"


/* function to execute a list of commands */
void executor(cmd *head)
{
	int status;
	cmd *curr = head;

	/* TODO: Add multiple executor sub functions to handle different separators and logicall operations */

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
