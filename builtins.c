#include "shell.h"

int _cd(char **args, char *name, int *count, int *status) 
{
	char *oldcwd, *newcwd, *msg1, *msg2, *errmsg;
	char newline = '\n';
	DIR *dir;

	(void)status;
	msg1 = _strcat(name, _strcat(_itoa(*count, 10), ": "));
	msg2 = _strcat("cd: can't cd to ", _strcat(args[1], "\n"));
	errmsg = _strcat(msg1, msg2);

	oldcwd = getcwd(NULL, 0);
	if (oldcwd == NULL)
		return(handle_errors(errmsg, 2));

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
				return(handle_errors(errmsg, 2));
			closedir(dir);
			newcwd = args[1];
		}
	}
	else
		newcwd = _getenv("HOME");

	if (chdir(newcwd) == -1) 
	    	return (handle_errors(NULL, 2));

	setenv("PWD", getcwd(NULL, 0), 1);
	setenv("OLDPWD", oldcwd, 1);
	return (0);
}




int _setenv(char **args, char *name, int *count, int *status)
{
	int i;
	int num_vars = 0;
	char **new_environ, *new_env, *msg1, *msg2, *errmsg;
	
	/* Error msg */
	(void)status;
	msg1 = _strcat(name, _strcat(_itoa(*count, 10), ": "));
	msg2 = "Usage: setenv VARIABLE VALUE \n";
	errmsg = _strcat(msg1, msg2);

	/* Handle Invalid User INPUT */
	if (args[1] == NULL || args[2] == NULL)
		return (handle_errors(errmsg, 2));

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
		return(handle_errors(NULL, 2));

	new_env = malloc(sizeof(char) * (strlen(args[1]) + strlen(args[2]) + 2));
	if (new_env == NULL)
		return(handle_errors(NULL, 2));

	for (i = 0; environ[i]; i++)
		new_environ[i] = environ[i];

	new_env = _strcat(_strcat(args[1], "="), args[2]);
	new_environ[i++] = new_env;
	new_environ[i] = NULL;
	environ = new_environ;
	return (0);
}




int _unsetenv(char **args, char *name, int *count, int *status)
{
	int i, target_index = -1;
	char *var_val, *whole_var = NULL, *msg1, *msg2, *errmsg;

	/* Error msg */
	(void)status;
	msg1 = _strcat(name, _strcat(_itoa(*count, 10), ": "));
	msg2 = "Usage: unsetenv VARIABLE VALUE \n";
	errmsg = _strcat(msg1, msg2);

	if (args[1] == NULL) 
		return(handle_errors(errmsg, 2));

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
			return (0);
		} 
	}

	return(handle_errors(errmsg, 2));
}



int _exit2(char **args, char *name, int *count, int *status)
{
	char *msg1, *msg2, *errmsg;
	int user_status;

	/* Error msg */
	msg1 = _strcat(name, _strcat(_itoa(*count, 10), ": "));
	msg2 = _strcat("exit: Illegal number: ", _strcat(args[1], "\n"));
	errmsg = _strcat(msg1, msg2);

	if (args[1] != NULL)
	{
		user_status = _atoi(args[1]);
		if (user_status <= 0)
			return(handle_errors(errmsg, 2));
		else
			exit(user_status);
	}
	exit(*status);
}

/**
 * _env - prints all the environmental variables
 *
 * Return: nothing.
 */
int _env(char **args, char *name, int *count, int *status)
{
	char *string;
	int i;
	(void)args;
	(void)name;
	(void)count;
	(void)status;

	for (i = 0; environ[i]; i++)
	{
		string = _strcat(environ[i], "\n");
		write(STDOUT_FILENO, string, _strlen(string));
	}

	return (0);
}
