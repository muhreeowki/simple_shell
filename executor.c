#include "shell.h"


/* function to execute a list of commands */
void executor(cmd **head)
{
	int status;
	cmd *curr = *head;

	/* TODO: Add multiple executor sub functions to handle different separators and logicall operations */
	while(curr != NULL)
	{
		pid_t pid = fork();

		if (pid == -1)
		{
			perror(NULL);
			exit(1);
		}
		else if (pid == 0)
		{
			if (execve(curr->name, curr->arguments, environ) == -1)
			{
				perror(NULL);
				exit(1);
			}
		}
		else
			wait(&status);

		curr = curr->next;
	}
}
