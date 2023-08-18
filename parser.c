#include "shell.h"

/* TODO: Check for seperators and logical opperators and append them to the seperators list */
/* TODO: if seperators are found, Repeat until we find all the commands. */

cmd *parser(char *input)
{
	cmd *head = NULL;
	char **arguments, **tokens, *separator;
	int i = 0, start = 0;

	/* function tokenization() - splits command into list of arguments and return list of args */
	tokens = tokenize(input, ' ');
	arguments = (tokens + start); 

	/* repeate until all commands have been collected */
	while(1)
	{
		/* loop through the list of tokens */
		while (tokens[i] != NULL)
		{
			/* Find the end of a command (a separator) */
			if ((tokens[i][0] == ';' || (tokens[i][0] == '&' && tokens[i][1] == '&') || 
				(tokens[i][0] == '|' && tokens[i][1] == '|')))
			{
				separator = _strdup(tokens[i]); /* duplicate the separator and store it in a var */
				tokens[i] = NULL; /* replace separator with NULL */
				head = append_cmd(head, arguments[0], arguments, separator); /* Append command to commands list */
				i++;
				start = i;
				arguments = (tokens + start); 
				break;
			}
			i++;
		}

		if (tokens[i] == NULL)
		{
			if(start != i)
				head = append_cmd(head, arguments[0], arguments, NULL); /* Append command to commands list */
			break;
		}
	}

	return (head);
}
