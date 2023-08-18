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



/*

   

int _setenv(char **args)
{
	
	if (args[1] == NULL || args[2] == NULL)
	{
		perror(
}

*/

/*
#include "shell.h"


int _cd(char **args) 
{
    char *cwd;

    if (getcwd(cwd, sizeof(cwd)) == NULL) 
    {
        perror("getcwd");
        return (-1);
    }
    cwd = getcwd(NULL, 0);
    if (args[1] == NULL) 
    {
        if (chdir(_getenv("HOME")) == -1) 
	{
            perror("chdir");
            return (-1);
        }
    } 
    else if (strcmp(args[1], "-") == 0) 
    {
        if (chdir(_getenv("OLDPWD")) == -1) 
	{
            perror("chdir");
            return (-1);
        }
    } 
    else 
    {
        if (chdir(args[1]) == -1) 
	{
            perror("chdir");
            return (-1);
        }
    }

    setenv("OLDPWD", cwd, 1);
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
    {
        setenv("PWD", cwd, 1);
    } 
    else 
    {
        perror("getcwd");
    }

    return (0);
}







*/
