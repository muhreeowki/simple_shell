#include "shell.h"


void executor(cmd **head)
{
	int status;
	cmd *curr = *head;

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
		{
			wait(&status);
		}
		curr = curr->next;
	}
}
