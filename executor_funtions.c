#include "shell.h"

/* 
   execute normall
   execute command seperator ;
   execute logical AND &&
   execute logical OR ||
 */

/* Checks if a program exists or not */
cmd *find_program(cmd *command, char **paths)
{
	int i;
	char *filepath;
	struct stat st;

	/* 1. check if the command is a builtin */
	for (i = 0; builtins[i].name != NULL; i++)
	{
		if(_strcmp(builtins[i].name, command->name) == 0)
		{
			command->builtin = 0;
			return (command);
		}
	}

	/* 2. check if the command name is a filepath */
	if (stat(command->name, &st) == 0)
	{
		command->builtin = 1;
		return (command);
	}

	/* 3. searching for the command in PATH */
	for (i = 0; paths[i] != NULL; i++)
	{
		filepath = _strcat(paths[i], _strcat("/", command->name));

		if (stat(filepath, &st) == 0)
		{
			command->name = filepath;
			command->builtin = 1;
			return (command);
		}
	}

	/* 4. Return 0 on succes and -1 on failur. */
	return (NULL);
}
