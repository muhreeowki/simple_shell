#include "shell.h"

int _cd(char **args) 
{
    if (args[1] == NULL) 
    {
        if (chdir(_getenv("HOME")) == -1) 
	{
            perror("chdir");
            return (-1);
        }
    } 
    else if (_strcmp(args[1], "-") == 0) 
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










