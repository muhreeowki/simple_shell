#include "shell.h"


/* How to get one line at a time */
ssize_t _getline(int fd, char **buff, size_t *size) 
{
	ssize_t bytes_read, buffsize = SSIZE_MAX;

	if (size)
		buffsize = *size > 0 ? *size : SSIZE_MAX;

	bytes_read = read(fd, *buff, buffsize);

	if(bytes_read == -1)
		return(handle_errors(NULL, 2));

	if(bytes_read == 0)
		return (-1);

	return (bytes_read);
}

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

char* _itoa(int num, int base)
{
    int i = 0, rem, test = num, size = 0;
    char *str;

    while (test > 0)
    {
	    test /= 10;
	    size++;
    }

    str = malloc(sizeof(char) * (size + 2));

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    while (num != 0) {
        rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    str[i] = '\0';

    reverse(str, i);

    return str;
}
