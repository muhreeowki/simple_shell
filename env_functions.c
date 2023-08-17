#include "shell.h"
/*
   TODO:
   Create _setenv
   Create _unsetenv
*/

/* function to get an environmental variable */
char *_getenv(char *var) /* PATH */
{
	int i, j;

	/* loop through environ */
	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; *(environ[i] + j) != '=' && var[j] != '\0'; j++)
		{
			if (var[j] != *(environ[i] + j))
				break;
		}

		if (var[j] == '\0' && *(environ[i] + j) == '=')
			return ((environ[i] + j + 1));
	}

	/* return NULL if we dont find anything */
	return (NULL);
}

/* Get the PATH and divide it into a list. */
char **get_paths(void)
{
	char *path_string, **paths;

	path_string = _getenv("PATH");
	paths = tokenize(path_string, ':');

	return (paths);
}
