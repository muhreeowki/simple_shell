#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

extern char **environ;

typedef struct cmd
{
	char *name;
	char **arguments;
	struct cmd *next;
	char *separator;
} cmd;

void executor(cmd *head);
cmd *parser(char *input, char **paths);
char *find_program(char *name, char **paths);
char **tokenize(char *input, char delim);
int count_tokens(char *input, char delim);
cmd *append_cmd(cmd *head, char *cmdname, char **arguments);
int _strcmp(char *s1, char *s2);
char **get_paths(void);
char *_getenv(char *var);
char *_strcat(char *s1, char *s2);
void free_cmdlist(cmd *head);
char *_strdup(char *str);
void remove_nl(char *input);

void print_cmd(cmd *head);
#endif
