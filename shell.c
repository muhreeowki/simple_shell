#include "shell.h"

/**
 * main - This is a UNIX command line interpreter.
 *
 * Return: nothing.
 */
int main(void)
{
	size_t size = MAX_INPUT_SIZE;
	char *input, **paths, nl = '\n';
	cmd *head = NULL;

	while (1)
	{
		input = malloc(sizeof(char) * size);
		if (input == NULL)
			continue;

		write(STDOUT_FILENO, "$ ", 2); /* Prompt */

		if (_getline(STDIN_FILENO, &input, &size) == -1) /* Get user input; exit on failur */
		{
			write(STDOUT_FILENO, &nl, 1);
			free(input);
			exit(0);
		}

		if (*input == '\n')
		{
			free(input);
			continue;
		}

		paths = get_paths(); /* Get PATH */

		head = parser(input); /* Parse user input into a command */

		if (head == NULL)
		{
			perror("parser");
			continue;
		}

		executor(head, paths);

		handle_free(input, head, paths);
	}
}

/**
 * handle_free - Handles freeing memory
 *
 * @input: user input buffer
 * @head: linked list of commands
 * @paths: list of paths in PATH
 *
 * Return: nothing.
 */
void handle_free(char *input, cmd *head, char **paths)
{
	free(input);
	free_cmdlist(head);
	free(paths);
}
