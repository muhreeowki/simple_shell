#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

typedef struct cmd
{
	char *name;
	char **arguments;
} cmd;

typedef struct cmd_node
{
	cmd *command;
	cmd *next;
} cmd_node;

#endif
