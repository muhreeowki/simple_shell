#include "shell.c"

char *_getenv(char *var)
{
	int i;

	/* loop through environ */
	for (i = 0; environ[i] != NULL, i++)
	{
		/* compare each variable with our var */
		if (_strcmp(environ[i], var) == 0)
			/* return a pointer to that variable if we find a match */
			return (environ[i]);
	}

	/* return NULL if we dont find anything */
	return (NULL);
}

/*
   _setenv
   _unsetenv
*/
