#include "shell.h"


/* How to get one line at a time */
ssize_t _getline(int fd, char **buff, size_t *size) 
{
	ssize_t bytes_read, buffsize = SSIZE_MAX;

	if (size)
		buffsize = *size > 0 ? *size : SSIZE_MAX;

	bytes_read = read(fd, *buff, buffsize);

	if(bytes_read == -1)
		return(handle_errors(NULL));

	if(bytes_read == 0)
		return (-1);

	return (bytes_read);
}
