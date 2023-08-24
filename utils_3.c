#include "shell.h"

/**
 * _getline - Read a line from a file descriptor
 * @fd: File descriptor to read from
 * @buff: Pointer to a buffer to store the line
 * @size: Pointer to the size of the buffer
 *
 * Return: Number of bytes read, or -1 on error or end of file
 */
ssize_t _getline(int fd, char **buff, size_t *size)
{
	ssize_t bytes_read, buffsize = SSIZE_MAX;

	if (size)
		buffsize = *size > 0 ? *size : SSIZE_MAX;

	bytes_read = read(fd, *buff, buffsize);

	if (bytes_read == -1)
		return (handle_errors(NULL, 2));

	if (bytes_read == 0)
		return (-1);

	return (bytes_read);
}

/**
 * reverse - Reverse a string in-place
 * @string: Pointer to the string to be reversed
 * @len: Length of the string
 */
void reverse(char *string, int len)
{
	int start, end = len - 1;
	char temp;

	for (start = 0, end = len - 1; start < end; start++, end--)
	{
		temp = string[start];
		string[start] = string[end];
		string[end] = temp;
	}
}

/**
 * _itoa - Convert an integer to a string
 * @num: The integer to be converted
 * @base: The base for conversion (e.g., 10 for decimal)
 *
 * Return: Pointer to the converted string
 */
char *_itoa(int num, int base)
{
	int i = 0, rem, test = num, size = 0;
	char *str;

	while (test > 0)
	{
		test /= 10;
		size++;
	}

	str = malloc(sizeof(char) * (size + 2));

	if (num == 0)
	{
		str[i++] = '0';
		str[i] = '\0';
		return (str);
	}

	while (num != 0)
	{
		rem = num % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / base;
	}

	str[i] = '\0';

	reverse(str, i);

	return (str);
}


/**
 * check_empty - Check if a string is empty or contains only whitespace
 * @string: Pointer to the string to be checked
 *
 * Return: -1 if the string is empty or contains only whitespace, 0 otherwise
 */
int check_empty(char *string)
{
	int i = 0;

	if (string == NULL)
		return (-1);

	for (i = 0; string[i] != '\0' && string[i] != '\n'; i++)
	{
		if (string[i] > 32 && string[i] < 127)
			return (0);
	}

	return (-1);
}
