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

	return (0);
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
	cmd *head = NULL;
	int i = 0, prompt_mode = 0, command_count = 1, exit_status = 0;
	char *input = NULL, **paths = NULL, **lines = NULL, nl = '\n',
	     *program_name = _strcat(argv[0], ": "), *empty = "_";
	(void)argv;
	while (1)
	{
		input = malloc(sizeof(char) * size);
		if (input == NULL)
			continue;
		prompt_mode = isatty(STDIN_FILENO);
		if (prompt_mode == 1)
			write(STDOUT_FILENO, "$ ", 2); /* Prompt */
		if (_getline(STDIN_FILENO, &input, &size) == -1)
		{
			if (prompt_mode == 1)
				write(STDOUT_FILENO, &nl, 1);
			free_all(input, NULL, program_name, NULL, NULL);
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
			exit_status = executor(head, paths, program_name,
					&command_count, &exit_status);
			free_cmdlist(head);
			free(paths[0]);
			free(paths);
		}
		free_all(input, lines, NULL, NULL, NULL);
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
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		free_all(NULL, NULL, program_name, errmsg[1], NULL);
		exit(handle_errors(msg, 127));
	}
	input = malloc(sizeof(char) * size);
	if (input == NULL)
	{
		free_all(NULL, NULL, program_name, errmsg[1], NULL);
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
			exit_status = executor(head, paths, program_name, &command_count, &exit_status);
			handle_free(NULL, head, paths);
		}
	}
	free_all(input, lines, errmsg[1], program_name, msg);
	close(fd);
	return (0);
}

void free_all(char *input, char **lines, char *program_name, char *errmsg1, char *msg)
{
	free(input);
	free(lines);
	free(program_name);
	free(errmsg1);
	free(msg);
}

