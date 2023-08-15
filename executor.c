#include "shell.h"


void executor(cmd **head , char **environ)
{
	cmd *curr = *head;
	while(curr != NULL)
	{
		pid_t pid = fork();

		if (pid < 0)
		{
			perror("Fork failed");
			exit(1);
		}
		else if (pid == 0)
		{
			execve(curr->name ,curr->arguments ,environ);
			perror("Command execution failed:");
			exit(1);
		}
		else
		{
			int status;
			wait(&status);
		}
		curr = curr->next;
	}
}

		

