#include "shell.h"

/**
 * _getenv - gets an environmental variable from the environment
 *
 * @var: variable to get
 *
 * Return: value of that variable
 */
char *_getenv(char *var)
{
	int i, j;

	if (environ == NULL || environ[0] == NULL)
		return (NULL);

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; var[j] != '\0'; j++)
		{
			if (var[j] != *(environ[i] + j))
				break;
		}

		if (var[j] == '\0' && *(environ[i] + j) == '='
			&& *(environ[i] + j + 1) != '\0')
			return ((environ[i] + j + 1));
	}

	return (NULL);
}

/**
 * get_paths - gets the PATH environmental variable
 * and divides it into its different paths.
 *
 * Return: list of all the paths in PATH
 */
char **get_paths(void)
{
	char *path_string, **paths = NULL;

	path_string = _getenv("PATH");
	if (path_string)
		paths = _strtok(path_string, ':');

	return (paths);
}

