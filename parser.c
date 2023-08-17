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
	printf("token[0]: %s\n", tokens[0]);

	/* repeate until all commands have been collected */
	while(1)
	{
		arguments = (tokens + start); 
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
				break;
			}
			i++;
		}

		if (tokens && tokens[i] == NULL)
		{
			head = append_cmd(head, arguments[0], arguments, separator); /* Append command to commands list */
			break;
		}
	}

	return (head);
}



/* PARSER 1
#include "shell.h"



cmd *parser(char *input)
{
	cmd *head = NULL;
	char **arguments, **tokens, *separator;
	int j = 0, i = 0, flag = 1, count = 0, start;

	while(1)
	{
		start = i;
		count = 0;
		flag = 1; 

		while (tokens[i] != NULL)
		{
			if ((tokens[i][0] == ';' || (tokens[i][0] == '&' && tokens[i][1] == '&') || 
				(tokens[i][0] == '|' && tokens[i][1] == '|')) && flag == 0)
			{

				arguments = malloc(sizeof(char *) * count + 1);
				if (arguments == NULL)
					return (NULL);
				for (j = 0; start < count; j++, start++)
				{
					printf("%s\n", tokens[start]);
					arguments[j] = tokens[start];
				}

				arguments[j] = NULL;

				separator = _strdup(tokens[i]); 

				head = append_cmd(head, arguments[0], arguments, separator);

				i++;
				break;
			}

			flag = 0;
			count++;
			i++;
		}
		if (tokens[i] == NULL)
			break;
	}

	return (head);
}
*/
