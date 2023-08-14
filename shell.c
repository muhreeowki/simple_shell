#include "shell.h"


int main(int argc, char **argv)
{
	extern char **environ;
	char *user_input = malloc(sizeof(char) * MAX_INPUT_SIZE);
	char *seperators = malloc(sizeof(char) * MAX_INPUT_SIZE);
	cmd_node **cmd_list;

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2); //Prompt

		// Get input
		if(getline(&user_input, MAX_INPUT_SIZE) == -1)
			return (0);

		user_input[strcspn(user_input, "\n")] = '\0'; //remove new line at end

		// call parser
		cmd_list = parser(user_input, seperators);
		if (cmd_list == NULL)
			perror("");

		// executor
		executor (cmd_list, seperators);
	}


	free(user_input);
	free(seperators);
	free(cmd_list);

	return (0);
}
