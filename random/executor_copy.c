#include "shell.h"


/* function to execute a list of commands */
void executor(cmd **head)
{
	int status;
	cmd *curr = *head;
	pid_t pid;

	/* TODO: Add multiple executor sub functions to handle different separators and logicall operations */
	while(curr != NULL)
	{
		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
		{
			execve(curr->name, curr->arguments, environ);
			perror("execve");
			exit(1);
		}

		curr = curr->next;
	}

	waitpid(pid, &status, 0);
}
