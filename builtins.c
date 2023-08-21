#include "shell.h"

int _cd(char **args) 
{
	char *oldcwd, *newcwd;
	DIR *dir;

	oldcwd = getcwd(NULL, 0);
	if (oldcwd == NULL)
		return(handle_errors("getcwd"));

	/* Handle empty arg */
	if (args[1]) 
	{
		if (args[1][0] == '-' && args[1][1] == '\0') 
			newcwd = _getenv("OLDPWD");
		else
		{
			dir = opendir(args[1]);
			if (!dir)
				return(handle_errors(NULL));
			closedir(dir);
			newcwd = args[1];
		}
	}
	else
		newcwd = _getenv("HOME");

	if (chdir(newcwd) == -1) 
	    	return (handle_errors("chdir"));

	setenv("PWD", getcwd(NULL, 0), 1);
	setenv("OLDPWD", oldcwd, 1);
	return (0);
}



   

int _setenv(char **args)
{
	int i;
	int num_vars = 0;
	char **new_environ, *new_env;
	
	/* Handle Invalid User INPUT */
	if (args[1] == NULL || args[2] == NULL)
		return (handle_errors("Usage: setenv VARIABLE VALUE"));

	/* Check if the variable exists */
	for (i = 0; environ[i] != NULL; i++)
	{
		if (_getenv(args[1]))
		{
			new_env = _strcat(_strcat(args[1], "="), args[2]);
			environ[i] = new_env;
			return (0);
		}
	}
	
	/* Count variables in environ */
	while (environ[num_vars])
		num_vars++;

	/* Reallocate a new list */
	new_environ = malloc((sizeof(char *)) * (num_vars + 2));
	if (new_environ == NULL)
		return(handle_errors(NULL));

	new_env = malloc(sizeof(char) * (strlen(args[1]) + strlen(args[2]) + 2));
	if (new_env == NULL)
		return(handle_errors(NULL));

	for (i = 0; environ[i]; i++)
		new_environ[i] = environ[i];

	new_env = _strcat(_strcat(args[1], "="), args[2]);
	new_environ[i++] = new_env;
	new_environ[i] = NULL;
	environ = new_environ;
	return (0);
}




int _unsetenv(char **args)
{
	int i, target_index = -1;
	char *var_val, *whole_var = NULL;

	if (args[1] == NULL) 
	{
		perror("Usage: unsetenv VARIABLE");
		return (-1);
	}

	/* Find the var */
	var_val = _getenv(args[1]);
	if (var_val)
	{
		whole_var = _strcat(_strcat(args[1], "="), var_val);
		for (i = 0; environ[i] != NULL; i++)
		{
			if (_strcmp(environ[i], whole_var) == 0)
			{
				target_index = i;
				free(environ[target_index]);
				break;
			}
		}

		if (target_index > 0)
		{
			/* Shift the rest of the environment variables to close the gap*/
			for (i = target_index; environ[i] != NULL; i++)
				environ[i] = environ[i + 1];
			return (0);
		}
		perror(NULL);
	}

	return (-1);
}



int _exit2(char **args)
{
	int def_status = 0, status;

	if (args[1] != NULL)
	{
		status = _atoi(args[1]);
		if (status == 0)
			exit(status);
	}

	exit(def_status);
}
