#include "shell.h"
/*


*/
int _cd(char **args)
{
	char *cwd = NULL;

	DIR *directory;
	struct dirent *dirstruct;
	if (getcwd(cwd, 0) == NULL)
	{
		perror("getcwd");
		return (-1);
	}
	printf("%s",cwd);
	if (access(cwd, X_OK) == -1)
	{
		perror("access");
		return (-1);
	}
	if (args[1] == NULL)
	{
		directory = opendir(_getenv("HOME"));
	}
	else if (_strcmp(args[1],"-") == 0)
	{
		directory = opendir(_getenv("OLDPWD"));
	}
	else
	{
		directory = opendir(args[1]);
	}	
	if (directory == NULL)
	{
		perror("opendir");
		return (-1);
	}
	dirstruct = readdir(directory);
	chdir(dirstruct->d_name);
/*	closedir(cwd);*/
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










