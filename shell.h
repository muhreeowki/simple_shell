#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

extern char **environ;

typedef struct cmd
{
	char *name;
	char **arguments;
	struct cmd *next;
	char separator = '\0';
} cmd;

void executor(cmd **head);
cmd **parser(char *input);
#endif
