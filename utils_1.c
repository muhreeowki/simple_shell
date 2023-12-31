#include "shell.h"

/**
 * _strcmp - Compares two strings.
 *
 * @s1: Pointer to the first string
 * @s2: Pointer to the second string
 *
 * Return: 0 if strings are equal, -1 otherwise
 */
int _strcmp(char *s1, char *s2)
{
	int i, j, len1, len2;

	i = j = len1 = len2 = 0;

	while (s1[len1] != '\0')
		len1++;

	while (s2[len2] != '\0')
		len2++;

	len1--;
	len2--;

	if (len1 != len2)
		return (-1);

	for (i = 0; i < len1; i++)
	{
		if (s1[i] != s2[i])
			return (-1);
	}

	return (0);
}


/**
 * _strcat2 - Concatenates multiple strings together.
 *
 * @strings: Array of strings to concatenate
 *
 * Return: Pointer to the concatenated string, or NULL on failure
 */
char *_strcat2(char **strings)
{
	int i, j, n, len;
	char *newstr;

	i = j = n = len = 0;
	if (strings == NULL)
		return (NULL);

	/* get length of all strings */
	for (i = 0; strings[i] != NULL; i++)
		len += _strlen(strings[i]);

	newstr = malloc(sizeof(char) * (len + 2));
	if (newstr == NULL)
	{
		perror(NULL);
		return (NULL);
	}

	for (i = 0; strings[i] != NULL; i++)
	{
		for (j = 0; strings[i][j] != '\0'; j++)
			newstr[n++] = strings[i][j];
	}

	newstr[n] = '\0';

	return (newstr);
}

/**
 * _strcat - Concatantes two strings together.
 *
 * @s1: pointer to string
 * @s2: pointer to string
 *
 * Return: Pointer to a new concatanted string
 */
char *_strcat(char *s1, char *s2)
{
	int i, j, len1, len2;
	char *newstr;

	i = j = len1 = len2 = 0;
	if (s1 == NULL)
		return (s2);
	if (s2 == NULL)
		return (s1);

	while (s1[len1] != '\0')
		len1++;

	while (s2[len2] != '\0')
		len2++;

	newstr = malloc(sizeof(char) * (len1 + len2 + 2));
	if (newstr == NULL)
	{
		perror(NULL);
		return (NULL);
	}

	for (i = 0; i < len1; i++)
		newstr[i] = s1[i];

	for (j = 0; j < len2; j++)
		newstr[i + j] = s2[j];

	newstr[i + j] = '\0';

	return (newstr);
}


/**
 * _strdup - creates a duplicate of a string.
 *
 * @str: pointer to string to duplicate
 *
 * Return: Pointer to string, or NULL if it fails.
 */
char *_strdup(char *str)
{
	int i, len;
	char *dupstr;

	len = 0;

	if (str == NULL)
		return (NULL);

	while (*(str + len) != '\0')
		len++;

	dupstr = malloc(sizeof(char) * (len + 1));

	if (dupstr == NULL)
		return (NULL);

	for (i = 0; i < len; i++)
		dupstr[i] = str[i];

	dupstr[i] = '\0';

	return (dupstr);
}

/**
 * remove_nl - Remove newline character and terminate string.
 *
 * @input: Input string to process.
 *
 * Return: nothing
 */
void remove_nl(char *input)
{
	int i;

	for (i = 0; input[i] != '\0'; i++)
	{
		if (input[i] == '\n')
		{
			input[i] = '\0';
			return;
		}
	}
}
