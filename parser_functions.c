#include "shell.h"


/* Checks if a program exists or not */
int find_program(char *name, char **paths)
{
	int i, count;
	char *filepath;

	/* 2. loop through the list of paths searching for the name */

	for (i = 0; paths[i] != NULL; i++)
	{
		filepath = _strcat(paths[i], name); /* TO BE CREATED */
		if (stat(filepath) == 0)
			return (0);
	}

	/* 3. Return 0 on succes and -1 on failur. */
	return (-1);
}




/* function tokenization() - splits command into list of arguments and return list of args */
char **tokenize(char *input)
{

	/* 3 */
	arguments_list = malloc(sizeof(char *) * (count + 1));
	if (arguments_list == NULL)
	{
		perror(NULL);
		return (NULL);
	}

	/* function _strtok() */
	/* get command name */
	arguments_list[0] = strtok(input, " ");

	/* split the arguments into the string */
	for (i = 1; i <= count; i++)
	{
		arguments_list[i] = strtok(NULL, " ");

	}

	return (arguments_list);
}




/* function to count number of tokens in a string */
int count_tokens(char *input)
{
	int i = 1;

	while (input[i] != '\0')
	{
		if (input[i] == ' ')
			count++;
		i++;
	}
}



