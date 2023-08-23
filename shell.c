#include "shell.h"

/**
 * main - This is a UNIX command line interpreter.
 *
 * Return: nothing.
 */
int main(int argc, char **argv)
{
	if (argc == 1)
		user_mode(argv);

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
int user_mode(char **argv)
{
	size_t size = MAX_INPUT_SIZE;
	char *input, **paths, **lines, nl = '\n', *program_name = _strcat(argv[0], ": "), *empty = "_";
	cmd *head = NULL;
	int i, prompt_mode, command_count = 1, exit_status = 0;

	(void)argv;
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
			free(program_name);
			exit(exit_status);
		}

		if (check_empty(input) == -1)
		{
			free(input);
			continue;
		}

		lines = _strtok(input, '\n');
		for (i = 0; lines[i]; i++)
		{
			paths = get_paths();
			if (paths == NULL)
				paths = &empty;
			head = parser(lines[i]);
			exit_status = executor(head, paths, program_name, &command_count, &exit_status);
			free_cmdlist(head);
			free(paths[0]);
			free(paths);
		}
		free(lines);
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
	int fd, j, command_count = 0, exit_status = 0;
	size_t size = MAX_INPUT_SIZE;
	cmd *head = NULL;
	char *msg, *input, **paths, **lines, *program_name = _strcat(argv[0], ": "),
	     *errmsg[15] = {NULL, NULL, ": ", "Can't open ", NULL, "\n", NULL};

	errmsg[0] = program_name;
	errmsg[1] = _itoa(command_count, 10);
	errmsg[4] = argv[1];
	msg = _strcat2(errmsg);

	/* Open the file */
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		free(program_name);
		free(errmsg[1]);
		exit(handle_errors(msg, 127));
	}

	/* allocate memory */
	input = malloc(sizeof(char) * size);
	if (input == NULL)
	{
		free(program_name);
		free(errmsg[1]);
		exit(handle_errors(NULL, 139));
	}

	/* Read line by line and execute each command */
	if (read(fd, input, size))
	{
		if (check_empty(input) == -1)
			return(2);

		lines = _strtok(input, '\n');
		for (j = 0; lines[j]; j++)
		{
			paths = get_paths();
			head = parser(lines[j]);
			exit_status = executor(head, paths, program_name, &command_count, &exit_status);
			handle_free(NULL, head, paths);
		}
	}

	free(input);
	free(lines);
	free(errmsg[1]);
	free(program_name);
	close(fd);
	return (0);
}
