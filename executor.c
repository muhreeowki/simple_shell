#include "shell.h"


/* function to execute a list of commands */
void executor(cmd **head)
{
	int status;
	cmd *curr = *head;

	/* TODO: Add multiple executor sub functions to handle different separators and logicall operations */
	printf("command name: %s\n1st argument: %s\n", curr->name, curr->arguments[0]);

	while(curr != NULL)
	{
		pid_t pid = fork();

		printf("command name: %s\n1st argument: %s\n", curr->name, curr->arguments[0]);
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
