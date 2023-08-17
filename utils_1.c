#include "shell.h"

/* compares two strings */
int _strcmp(char *s1, char *s2)
{
	/* loop through each string, if the strings do not match return -1, if they match return 0*/
	int i, j, len1, len2;

	i = j = len1 = len2 = 0;

	/* get the length of both strings */
	while (s1[len1] != '\0')
		len1++;

	while (s2[len2] != '\0')
		len2++;

	len1--;
	len2--;

	/* if strings are not the same length they dont match */
	if (len1 != len2)
		return (-1);

	/* loop through the strings and compare their chars */
	/* strings are the same length */
	for (i = 0; i < len1; i++)
	{
		if (s1[i] != s2[i])
			return (-1);
	}

	return (0);
}



/**
 * _strcat - Concatantes two strings together.
 *
 * @src: pointer to string that is being appended
 * @dest: pointer to string that is being concatanated
 *
 * Return: Pointer to concatanted string
 */

char *_strcat(char *s1, char *s2)
{
	/* loop through each string, if the strings do not match return -1, if they match return 0*/
	int i, j, len1, len2;
	char *newstr;

	i = j = len1 = len2 = 0;

	/* get the length of both strings */
	while (s1[len1] != '\0')
		len1++;

	while (s2[len2] != '\0')
		len2++;

	/* allocate memory for the new string */
	newstr = malloc(sizeof(len1 + len2 + 1));
	if (newstr == NULL)
	{
		perror(NULL);
		return (NULL);
	}

	/* add s1 to newstr */
	for (i = 0; i < len1; i++)
		newstr[i] = s1[i];

	/* add s2 to newstr */
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
	len--;

	dupstr = malloc(sizeof(char) * len + 1);

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

	/* Find the newline character and replace it with null terminator */
	for (i = 0; input[i] != '\0'; i++) 
	{
		if (input[i] == '\n') 
		{
			input[i] = '\0';
			return;
		}
	}
}
