#include "shell.h"

int main(void)
{
	size_t size = MAX_INPUT_SIZE;
	char *input;
	char **paths;
	cmd *head = NULL;
	char nl = '\n';
	
	while (1)
	{
		input = malloc(sizeof(char) * size);
		if (input == NULL)
		{
			perror(NULL);
			return(-1);
		}
		
		write(STDOUT_FILENO, "$ ", 2); /* Prompt */

		if(getline(&input, &size, stdin) == -1) /* Get user input */
		{
			/* exit on failur */
			write(STDOUT_FILENO, &nl, 1);
			free(input);
			return(0);
		}

		paths = get_paths(); /* Get PATH */


		remove_nl(input);
		if (*input == '\0')
			continue;

		head = parser(input); /* Parse user input into a command */

		if (head == NULL)
		{
			perror("parser");
			continue;
		}

		executor(head, paths);
		/*
		print_cmd(head);
		*/

		/* free memory */
		free(input);
		free_cmdlist(head);
		free(paths);
	}

	return (0);
}
