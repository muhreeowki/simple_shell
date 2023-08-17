#include "shell.h"

int main(void)
{
	size_t size = MAX_INPUT_SIZE;
	char *user_input;
	char **paths;
	cmd *head = NULL;
	char nl = '\n';
	
	while (1)
	{
		user_input = malloc(sizeof(char) * size);
		if (user_input == NULL)
		{
			perror(NULL);
			return(-1);
		}

		
		write(STDOUT_FILENO, "$ ", 2); /* Prompt */

		if(getline(&user_input, &size, stdin) == -1) /* Get user input */
		{
			/* exit on failur */
			write(STDOUT_FILENO, &nl, 1);
			free(user_input);
			return(0);
		}

		paths = get_paths(); /* Get PATH */

		remove_nl(user_input);
		if (*user_input == '\0')
			continue;

		head = parser(user_input); /* Parse user input into a command */

		if (head == NULL)
		{
			perror("parser");
			continue;
		}

		print_cmd(head);

		/*
		executor(head);
		*/

		/* free memory */
		free(user_input);
		free_cmdlist(head);
		free(paths);
	}

	return (0);
}
