#include "shell.h"

int main(void)
{
	size_t size = MAX_INPUT_SIZE;
	char *user_input = malloc(sizeof(char) * size);
	char **paths;
	cmd **cmd_list;
	char nl = '\n';
	int i;

	while (1)
	{
		paths = get_paths();

		write(STDOUT_FILENO, "$ ", 2); /*Prompt*/

		/* Get input*/
		if(getline(&user_input, &size, stdin) == -1)
		{
			write(STDOUT_FILENO, &nl, 1);
			return(0);
		}

		user_input[strcspn(user_input, "\n")] = '\0'; /*remove new line at end*/

		/* call parser*/
		cmd_list = parser(user_input, paths);

		if (cmd_list == NULL)
			perror("");

		/* executor*/
		executor (cmd_list);
	}

	free(user_input);
	for (i = 0; cmd_list[i] != NULL; i++)
	{
		free(cmd_list[i]->arguments);
		free(cmd_list[i]);
	}

	free(cmd_list);

	return (0);
}


/* Get the PATH and divide it into a list. */
char **get_paths(void)
{
	char *path_string = _getenv("PATH");
	char **paths = tokenize(path_string, ':'); /* TO BE CREATED */

	return (paths);
}
