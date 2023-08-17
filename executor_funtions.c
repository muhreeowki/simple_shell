#include "shell.h"

/* 
   execute normall
   execute command seperator ;
   execute logical AND &&
   execute logical OR ||
 */

/* Checks if a program exists or not */
char *find_program(char *name, char **paths)
{
	int i;
	char *filepath;
	struct stat st;

	/* 1. check if the users inputed a filepath */
	if (stat(name, &st) == 0)
		return (name);

	/* 2. loop through the list of paths searching for the name */
	for (i = 0; paths[i] != NULL; i++)
	{
		filepath = _strcat(paths[i], _strcat("/", name));

		if (stat(filepath, &st) == 0)
			return (filepath);

		else 
			continue;
	}

	/* 3. Return 0 on succes and -1 on failur. */
	return (NULL);
}
