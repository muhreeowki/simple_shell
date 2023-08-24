#include "shell.h"

/**
 * main - This is a UNIX command line interpreter.
 *
 * @argc: number of command line arguments
 * @argv: list of command line arguments
 *
 * Return: nothing.
 */
int main(int argc, char **argv)
{
	if (argc == 1)
		user_mode(argv);

	if (argc >= 2)
		file_mode(argv);

	return (0);
}

/**
 * user_mode - This is the interactive user mode
 * for our shell program
 *
 * @argv: list of command line arguments
 *
 * Return: nothing.
 */
int user_mode(char **argv)
{
	size_t size = MAX_INPUT_SIZE;
	cmd *head = NULL;
	int i = 0, prompt_mode = 0, count = 1, exit_status = 0;
	char *input = NULL, **paths = NULL, **lines = &input, nl = '\n';
	char *name = _strcat(argv[0], ": "), *empty = "_";
	(void)argv;
	while (1)
	{
		input = malloc(sizeof(char) * size);
		if (input == NULL)
			continue;
		memset(input, 0, size);
		prompt_mode = isatty(STDIN_FILENO);
		if (prompt_mode == 1)
			write(STDOUT_FILENO, "($) ", 4); /* Prompt */
		if (_getline(STDIN_FILENO, &input, &size) == -1)
		{
			if (prompt_mode == 1)
				write(STDOUT_FILENO, &nl, 1);
			free(input);
			exit(exit_status);
		}
		if (check_empty(input) == -1)
		{
			free(input);
			continue;
		}
		lines = _strtok(input, nl);
		while (lines[i])
		{
			paths = get_paths();
			paths = paths == NULL ? &empty : paths;
			head = parser(lines[i++]);
			exit_status = executor(head, paths, name, &count, &exit_status);
			free(paths[0]);
			free(paths);
			free_cmdlist(head);
		}
		free(input);
		free(lines);
	}
	free(name);
}

/**
 * file_mode - This is a none interactive mode
 * to execute files.
 *
 * @argv: list of command line arguments
 *
 * Return: nothing.
 */
int file_mode(char **argv)
{
	int fd, j, count = 0, exit_status = 0;
	size_t size = MAX_INPUT_SIZE;
	cmd *head = NULL;
	char *msg, *input, **paths, **lines, *name = _strcat(argv[0], ": "),
	     *errmsg[15] = {NULL, NULL, ": ", "Can't open ", NULL, "\n", NULL};

	errmsg[0] = name;
	errmsg[1] = _itoa(count, 10);
	errmsg[4] = argv[1];
	msg = _strcat2(errmsg);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		free_all(NULL, NULL, name, errmsg[1], NULL);
		exit(handle_errors(msg, 127));
	}
	input = malloc(sizeof(char) * size);
	if (input == NULL)
	{
		free_all(NULL, NULL, name, errmsg[1], NULL);
		exit(handle_errors(NULL, 139));
	}
	if (read(fd, input, size))
	{
		if (check_empty(input) == -1)
			return (2);
		lines = _strtok(input, '\n');
		for (j = 0; lines[j]; j++)
		{
			paths = get_paths();
			head = parser(lines[j]);
			exit_status = executor(head, paths, name, &count, &exit_status);
			handle_free(NULL, head, paths);
		}
	}
	free_all(input, lines, errmsg[1], name, msg);
	close(fd);
	return (0);
}


/**
 * free_all - function to free memory
 *
 * @input: pointer
 * @lines: pointer
 * @name: pointer
 * @errmsg1: pointer
 * @msg: pointer
 *
 * Return: nothing.
 */
void free_all(char *input, char **lines, char *name, char *errmsg1, char *msg)
{
	free(input);
	free(lines);
	free(name);
	free(errmsg1);
	free(msg);
}

