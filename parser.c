#include "shell.h"


/**
 * parser - parses a string into list of command nodes
 *
 * @input: pointer to string
 *
 * Return: pointer to a list of commands
 */
cmd *parser(char *input)
{
	cmd *head = NULL;
	char **arguments, **tokens, *separator;
	int i = 0, start = 0;

	remove_nl(input);
	tokens = tokenize(input, ' ');
	arguments = (tokens + start);

	while (1)
	{
		while (tokens[i] != NULL)
		{
			if ((tokens[i][0] == ';' || (tokens[i][0] == '&' && tokens[i][1] == '&') ||
				(tokens[i][0] == '|' && tokens[i][1] == '|')))
			{
				separator = _strdup(tokens[i]);
				tokens[i] = NULL;
				head = append_cmd(head, arguments[0], arguments, separator);
				start = ++i;
				arguments = (tokens + start);
				break;
			}
			i++;
		}

		if (tokens[i] == NULL)
		{
			if (start != i)
				head = append_cmd(head, arguments[0], arguments, NULL);
			break;
		}
	}

	return (head);
}
