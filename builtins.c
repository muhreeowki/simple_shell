#include "shell.h"

int _cd(char **args) 
{
	char *cwd;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd");
		return (-1);
	}
	if (args[1] == NULL) 
	{
		if (chdir(_getenv("HOME")) == -1) 
		{
		    perror("chdir");
		    return (-1);
		}
		cwd = getcwd(NULL, 0);
		setenv("PWD", cwd, 1);
	} 
	else if (_strcmp(args[1], "-") == 0) 
	{
		if (chdir(_getenv("OLDPWD")) == -1) 
		{
		    perror("chdir");
		    return (-1);
		}
		cwd = getcwd(NULL, 0);
		setenv("PWD", cwd, 1);
	} 
	else 
	{
		if (chdir(args[1]) == -1) 
		{
		    perror("chdir");
		    return (-1);
		}
		cwd = getcwd(NULL, 0);
		setenv("PWD", cwd, 1);
	}
	
	setenv("OLDPWD", cwd, 1);


	return (0);
}



   

int _setenv(char **args)
{
	int i;
	int num_vars = 0;
	char **new_environ;
	char *new_env;
	
	if (args[1] == NULL || args[2] == NULL)
	{
		perror(NULL);
		return (-1);
	}
	for (i = 0; environ[i] != NULL; i++)
	{
		environvar = _getenv(args[1]);
		if (environvar)
		{
			char *new_environ;
			new_environ = malloc(_strlen(args[1]) + _strlen(args[2]) + 1);
			if (new_environ == NULL)
			{
				perror(NULL);
				return(-1);
			}

			*args = new_environ;
			environ[i] = new_environ;
			return (0);
		}
	}
	
	while(environ[num_vars] != NULL)
		num_vars++;

	new_environ = realloc(environ, (num_vars + 1) * sizeof(char *));
	if (new_environ == NULL)
	{
		perror(NULL);
		return(-1);
	}
	new_env = malloc(strlen(args[1]) + strlen(args[2]) + 1);
	if (new_env == NULL)
	{
		perror("malloc");
		return 1;
	}
	*args = new_env;
	new_environ[num_vars] = new_env;
	new_environ[num_vars + 1] = NULL;
	environ = new_environ;

	return (0);
}




int _unsetenv(char **args)
{
	int i;
	int target_index = -1;

	if (args[1] == NULL) 
	{
		perror(NULL);
		return (1);
	}

	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strcmp(environ[i], args[1]) == 0)
		{
			target_index = i;
			break;
		}
	}

	if (target_index == -1)
	{
		perror(NULL);

		return (1);
	}

	free(environ[target_index]);
	/* Shift the rest of the environment variables to close the gap*/
	for (i = target_index; environ[i] != NULL; i++)
	{
		environ[i] = environ[i + 1];
	}

	return (0);
}





int _exit2(char **args)
{
	int status;

	if (args[1] != NULL)
	{
		status = atoi(args[1]);
	}
	exit(status);
	
}
