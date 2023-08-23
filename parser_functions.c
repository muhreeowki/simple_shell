#include "shell.h"

/**
 * tokenize - divides a string input into a list of tokens/words
 * (similar to _strtok)
 *
 * @input: pointer to string
 *
 * Return: Pointer to list of string
 */
char **tokenize(char *input)
{
	int i = 0, count = 0, n = 0, flag = 1, start = 0;
	char **arguments_list = NULL, *substring = NULL, *string = input;
	char *separators[] = {";", "&&", "||"};

	count = _strlen(string);
	arguments_list = malloc(sizeof(char *) * (count));
	if (arguments_list == NULL)
	{
		perror(NULL);
		return (NULL);
	}

	/* initialize the arguments list */
	for (i = 0; i < count ; i++)
		arguments_list[i] = NULL;

	for (i = 0; string[i] != '\0'; i++)
	{
		if (flag == 1)
		{
			if (string[i] >= 32 && string[i] < 127)
			{
				flag = 0;
				start = i;
				substring = (string + start);
			}
		}

		if (flag == 1)
			continue;

		flag = divide_sep(string, arguments_list, separators, substring, &i, &n);
	}
	if (flag == 0)
		arguments_list[n] = substring;

	return (arguments_list);
}

/**
 * divide_sep - helper function for tokenize
 *
 * @string: pointer to string
 * @arguments_list: pointer to a list of arguments
 * @separators: list of separators
 * @substring: pointer to a string
 * @i: index
 * @n: index
 *
 * Return: Pointer to list of string
 */
int divide_sep(char *string, char **arguments_list,
		char **separators, char *substring, int *i, int *n)
{
	if (string[*i] == ' ')
	{
		string[*i] = '\0';
		if (string[*i - 1] > 32 && string[*i - 1] < 127)
			arguments_list[(*n)++] = substring;
		substring = (string + *i + 1);
		return (1);
	}
	if (string[*i] == ';')
	{
		string[*i] = '\0';
		if (string[*i - 1] > 32 && string[*i - 1] < 127)
			arguments_list[(*n)++] = substring;
		arguments_list[(*n)++] = separators[0];
		substring = (string + *i + 1);
		return (1);
	}
	if (string[*i] == '&' && string[*i + 1] == '&')
	{
		string[(*i)++] = '\0';
		string[*i] = '\0';
		if (string[*i - 2] > 32 && string[*i - 2] < 127)
			arguments_list[(*n)++] = substring;
		arguments_list[(*n)++] = separators[1];
		substring = (string + *i + 1);
		return (1);
	}
	if (string[*i] == '|' && string[*i + 1] == '|')
	{
		string[*i] = '\0';
		string[*i + 1] = '\0';
		if (string[*i - 2] > 32 && string[*i - 2] < 127)
			arguments_list[(*n)++] = substring;
		arguments_list[(*n)++] = separators[2];
		substring = (string + *i + 2);
		return (1);
	}
	return (0);
}


/**
 * _strtok - divides a string input into a list of tokens/words
 * (similar to _strtok)
 *
 * @input: pointer to string
 * @delim: delimiter to divide the string by
 *
 * Return: Pointer to list of string
 */
char **_strtok(char *input, const char delim)
{
	int i = 0, count = 0, n = 0, flag = 1, start = 0;
	char **arguments_list = NULL, *substring = NULL, *string = input;

	/*string = input;*/
	count = count_tokens(string, delim);
	arguments_list = malloc(sizeof(char *) * (count + 1));
	if (arguments_list == NULL)
	{
		perror(NULL);
		return (NULL);
	}

	while (string[i] != 0)
	{
		if (flag == 1)
		{
			start = i;
			substring = (string + start);
			flag = 0;
		}
		if (string[i] == delim)
		{
			if (flag == 1)
				continue;
			string[i] = '\0';
			flag = 1;
			if (string[i - 1] >= 32 && string[i - 1] < 127)
				arguments_list[n++] = substring;
		}
		i++;
	}

	if (string[i - 1] >= 31 && string[i - 1] < 127)
		arguments_list[n] = substring;

	return (arguments_list);
}

/**
 * count_tokens - counts the number of tokens/words in a string
 *
 * @input: pointer to string
 * @delim: delimiter to divide the string by
 *
 * Return: Pointer to list of string
 */
int count_tokens(char *input, char delim)
{
	int i = 0, count = 1;
	char *string = NULL;

	string = input;
	while (string[i] != '\0')
	{
		if (string[i++] == delim)
			count++;
	}

	return (count);
}


/**
 * append_cmd - appends a command to a linked list of commands
 *
 * @head: pointer to head of list
 * @cmdname: name of command
 * @arguments: pointer to a list of arguments strings
 * @sep: pointer to the separator
 *
 * Return: Pointer to head of list
 */
cmd *append_cmd(cmd *head, char *cmdname, char **arguments, char *sep)
{
	cmd *new = malloc(sizeof(cmd)), *curr = head;

	if (new == NULL)
	{
		perror(NULL);
		return (NULL);
	}

	new->builtin = -1;
	new->name = cmdname;
	new->arguments = arguments;
	new->separator = sep;
	new->function = NULL;
	new->next = NULL;

	if (head == NULL)
		return (new);

	while (curr->next)
		curr = curr->next;

	curr->next = new;

	return (head);
}
