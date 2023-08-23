#include "shell.h"

int _cd(char **args, char *name, int *count, int *status) 
{
	DIR *dir;
	char *oldcwd, *newcwd, *msg, newline = '\n', 
	     *errmsg[15] = {NULL, NULL, ": ", "cd: can't cd to ", NULL, "\n", NULL};

	errmsg[0] = name;
	errmsg[1] = _itoa(*count, 10);
	errmsg[4] = args[1];
	msg = _strcat2(errmsg);
	free(errmsg[1]);

	oldcwd = getcwd(NULL, 0);
	if (oldcwd == NULL)
		return(handle_errors(msg, 2));

	if (args[1]) 
	{
		if (args[1][0] == '-' && args[1][1] == '\0')
		{
			newcwd =_getenv("OLDPWD");
			write(STDOUT_FILENO, newcwd, _strlen(newcwd));
			write(STDOUT_FILENO, &newline, 1);
		}
		else
		{
			dir = opendir(args[1]);
			if (dir == NULL)
				return(handle_errors(msg, 2));
			closedir(dir);
			newcwd = args[1];
		}
	}
	else
		newcwd = _getenv("HOME");

	if (chdir(newcwd) == -1) 
	    	return (handle_errors(NULL, 2));

	setenv("OLDPWD", oldcwd, 1);
	setenv("PWD", newcwd, 1);
	free(oldcwd);
	(void)status;
	free(msg);
	return (0);
}




int _setenv(char **args, char *name, int *count, int *status)
{
	int i;
	int num_vars = 0;
	char **new_environ, *new_env, *msg, 
	     *errmsg[6] = {NULL, NULL, ": ", "Usage: setenv VARIABLE VALUE \n", NULL}, 
	     *array[4] = {NULL, "=", NULL, NULL};

	/* Error msg */
	errmsg[0] = name;
	errmsg[1] =  _itoa(*count, 10);
	array[0] = args[1];
	array[2] = args[2];
	new_env = _strcat2(array);
	msg = _strcat2(errmsg);
	free(errmsg[1]);

	(void)status;
	/* Handle Invalid User INPUT */
	if (args[1] == NULL || args[2] == NULL)
		return (handle_errors(msg, 2));

	/* Check if the variable exists */
	for (i = 0; environ[i] != NULL; i++)
	{
		if (_getenv(args[1]))
		{
			environ[i] = new_env;
			free(msg);
			return (0);
		}
	}
	
	/* Count variables in environ */
	while (environ[num_vars])
		num_vars++;

	/* Reallocate a new list */
	new_environ = malloc((sizeof(char *)) * (num_vars + 2));
	if (new_environ == NULL)
		return(handle_errors(NULL, 2));

	new_env = malloc(sizeof(char) * (strlen(args[1]) + strlen(args[2]) + 2));
	if (new_env == NULL)
		return(handle_errors(NULL, 2));

	for (i = 0; environ[i]; i++)
		new_environ[i] = environ[i];

	new_environ[i++] = new_env;
	new_environ[i] = NULL;
	environ = new_environ;
	free(msg);
	return (0);
}

 
int _unsetenv(char **args, char *name, int *count, int *status)
{
	int i, target_index = -1;
	char *var_val, *whole_var = NULL, *msg, 
	     *errmsg[6] = {NULL, NULL, ": ", "Usage: unsetenv VARIABLE\n", NULL}, 
	     *array[6] = {NULL, "=", NULL, NULL, NULL};

	/* Error msg */
	errmsg[0] = name;
	errmsg[1] =  _itoa(*count, 10);
	msg = _strcat2(errmsg);
	free(errmsg[1]);
	(void)status;

	if (args[1] == NULL) 
		return(handle_errors(msg, 2));

	/* Find the var */
	var_val = _getenv(args[1]);
	if (var_val)
	{
		array[0] = args[1];
		array[2] = var_val;
		whole_var = _strcat2(array);
		for (i = 0; environ[i] != NULL; i++)
		{
			if (_strcmp(environ[i], whole_var) == 0)
			{
				target_index = i;
				/*free(environ[target_index]);*/
				break;
			}
		}

		if (target_index >= 0)
		{
			for (i = target_index ; environ[i] != NULL; i++)
				environ[i] = environ[i + 1];
		/*	for (i = target_index + 1; environ[i] != NULL; i++)
				environ[i - 1] = environ[i];*/
			free(msg);
			return (0);
		} 
	}

	return(handle_errors(msg, 2));
}



int _exit2(char **args, char *name, int *count, int *status)
{
	int user_status;
	char *msg, *errmsg[15] = {NULL, NULL, ": ", "exit: Illegal number: ", NULL, "\n", NULL};

	/* Error msg */
	errmsg[0] = name;
	errmsg[1] = _itoa(*count, 10);
	errmsg[4] = args[1];
	msg = _strcat2(errmsg);
	free(errmsg[1]);

	if (args[1] != NULL)
	{
		user_status = _atoi(args[1]);
		if (user_status <= 0)
			return(handle_errors(msg, 2));
		else
			exit(user_status);
	}
	free(msg);
	exit(*status);
}

/**
 * _env - prints all the environmental variables
 *
 * Return: nothing.
 */
int _env(char **args, char *name, int *count, int *status)
{
	char *string = NULL;
	int i;
	(void)args;
	(void)name;
	(void)count;
	(void)status;

	for (i = 0; environ[i]; i++)
	{
		string = _strcat(environ[i], "\n");
		write(STDOUT_FILENO, string, _strlen(string));
		if(string)
			free(string);
	}

	return (0);
}
