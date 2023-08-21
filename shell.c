#include "shell.h"

/**
 * main - This is a UNIX command line interpreter.
 *
 * Return: nothing.
 */
int main(int argc, char **argv)
{
	if (argc == 1)
		user_mode();

	if (argc >= 2)
		file_mode(argv);

	return(0);
}

/**
 * user_mode - This is the interactive user mode
 * for our shell program
 *
 * Return: nothing.
 */
int user_mode(void)
{
	size_t size = MAX_INPUT_SIZE;
	char *input, **paths, **lines, nl = '\n';
	cmd *head = NULL;
	int i, prompt_mode;

	while (1)
	{
		input = malloc(sizeof(char) * size);
		if (input == NULL)
			continue;

		prompt_mode = isatty(STDIN_FILENO);
		if (prompt_mode == 1)
			write(STDOUT_FILENO, "$ ", 2); /* Prompt */

		/* Get user input; exit on failur */
		if (_getline(STDIN_FILENO, &input, &size) == -1) 
		{
			if (prompt_mode == 1)
				write(STDOUT_FILENO, &nl, 1);
			free(input);
			exit(0);
		}

		if (check_empty(input) == -1)
		{
			free(input);
			continue;
		}

		lines = tokenize(input, '\n');
		for (i = 0; lines[i]; i++)
		{
			paths = get_paths();
			head = parser(lines[i]);

			if (head == NULL)
				return(handle_errors(NULL));

			executor(head, paths);

			handle_free(NULL, head, paths);
		}
		free(input);
	}
}

/**
 * file_mode - This is a none interactive mode
 * to execute files.
 *
 * Return: nothing.
 */
int file_mode(char **argv)
{
	int fd, i, j;
	size_t size = MAX_INPUT_SIZE;
	char *input, **paths, **lines;
	cmd *head = NULL;

	for (i = 1, j = 0; argv[i] != NULL; i++)
	{
		/* Open the file */
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			return (handle_errors(NULL));

		/* allocate memory */
		input = malloc(sizeof(char) * size);
		if (input == NULL)
			return (handle_errors(NULL));

		/* Read line by line and execute each command */
		while (read(fd, input, size))
		{
			if (check_empty(input) == -1)
				continue;

			lines = tokenize(input, '\n');
			for (j = 0; lines[j]; j++)
			{
				paths = get_paths(); /* Get PATH */
				head = parser(lines[j]); /* Parse user input into a command */

				if (head == NULL)
					return(handle_errors(NULL));

				executor(head, paths);

				handle_free(NULL, head, paths);
			}

		}
		free(input);
	}

	return (0);
}
