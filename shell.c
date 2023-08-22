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
	char *input, **paths, **lines, nl = '\n', *program_name = _strcat(argv[0], ": ");
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
			head = parser(lines[i]);
			exit_status = executor(head, paths, program_name, &command_count, &exit_status);
			handle_free(NULL, head, paths);
		}
		free(input);
	}
	free(program_name);
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
	char *input, **paths, **lines, *program_name = _strcat(argv[0], ": "), 
	     *msg1, *msg2, *msg3, *msg4, *errmsg;
	cmd *head = NULL;

	msg1 = _strcat(_itoa(command_count, 10), ": ");
	msg2 = _strcat(program_name, msg1);
	msg3 = _strcat(msg2, "Can't open ");
	msg4 = _strcat(argv[1], "\n");
	errmsg = _strcat(msg3, msg4);

	/* Open the file */
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit(handle_errors(errmsg, 127));

	/* allocate memory */
	input = malloc(sizeof(char) * size);
	if (input == NULL)
		exit(handle_errors(NULL, 139));

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
	free(msg1);
	free(msg2);
	free(msg3);
	free(msg4);
	free(program_name);

	return (0);
}
