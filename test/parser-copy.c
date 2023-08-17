#include "shell.h"

cmd *parser(char *input) 
{
	char **tokens;
    	cmd *head = NULL;
	char *separator;

	/* function tokenization() - splits command into list of arguments and return list of args */
	tokens = tokenize(input, ' ');
    
        while (tokens[0] != NULL) 
	{
		int i = 0;
		int j;
		char **command_tokens = malloc(sizeof(char *) * (i + 1));

		while (tokens[i] != NULL) 
		{
		    if (tokens[i][0] == ';' || tokens[i][0] == '&' || tokens[i][0] == '|') {
			separator = tokens[i];
			break;
		    }
		    i++;
		}
		

		for (j = 0; j < i; j++) 
		{
		    command_tokens[j] = strdup(tokens[j]);
		}
		command_tokens[i] = NULL;
		

		for (j = i + 1; tokens[j] != NULL; j++) {
		    tokens[j - i - 1] = tokens[j];
		}

		tokens[j - i - 1] = NULL;
		head = append_cmd(head, command_tokens[0], command_tokens, separator); /* Append command to commands list */
    	}
    
    return head;
}
