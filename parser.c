#include "shell.h"


cmd_node **parser(char *input, char *seperators)
{
	char *command_name;
	char **arguments_list;
	cmd_node **head;
	int i = 0, count = 1;


	/* Tokenization */

	/* count args */
	while (input[i] != '\0')
	{
		if (input[i] == ' ')
			count++;
	}

	/* 3 */
	arguments_list = malloc(sizeof(char *) * count + 1);

	/* get command name */
	command_name = strtok(input, ' ');

	/* split the arguments into the string */

	for (i = 0; i < count; i++)
	{
		arguments_list[i] = strtok(input, ' ');
		if (arguments_list[i] == NULL)
			break;

		/* TODO: Check for seperators and logical opperators and append them to the seperators list */
	}

	arguments_list[i] = NULL;

	/* Initialization of command */
	/* Append command to list */
	/* TODO: if seperators are found, Repeat until we find all the commands. */
}
