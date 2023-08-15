#include "shell.h"


int main(void)
{
	extern char **environ;
	char *user_input = malloc(sizeof(char) * MAX_INPUT_SIZE);
	cmd **cmd_list;
	int i;
	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2); /*Prompt*/

		/* Get input*/
		if(getline(&user_input, (size_t *)MAX_INPUT_SIZE, stdin) == -1)
			continue;
		user_input[strcspn(user_input, "\n")] = '\0'; /*remove new line at end*/

		/* call parser*/
		cmd_list = parser(user_input);
		if (cmd_list == NULL)
			perror("");

		/* executor*/
		executor (cmd_list,environ);
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
