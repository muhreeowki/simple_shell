#include "shell.h"

int main(void)
{
	size_t size = MAX_INPUT_SIZE;
	char *user_input = malloc(sizeof(char) * size);
	char **paths;
	cmd **cmd_list;
	char nl = '\n';

	while (1)
	{
		paths = get_paths();

		write(STDOUT_FILENO, "$ ", 2); /*Prompt*/

		/* Get user input */
		if(getline(&user_input, &size, stdin) == -1)
		{
			/* exit */
			write(STDOUT_FILENO, &nl, 1);
			free(user_input);
			/* Create a function to FREE the cmdlist (linked list) and all the commands inside it */
			return(0);
		}

		user_input[strcspn(user_input, "\n")] = '\0'; /* Create remove_nl function */

		/* Parser */
		cmd_list = parser(user_input, paths);

		if (cmd_list == NULL)
		{
			perror(NULL);
			continue;
		}

		executor(cmd_list);
	}

	return (0);
}
