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
