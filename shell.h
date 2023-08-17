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

/* our structs */
typedef struct cmd
{
	char *name;
	char **arguments;
	char *separator;
	struct cmd *next;
} cmd;

/* parser functions */
cmd *parser(char *input, char **paths);
char *find_program(char *name, char **paths);
char **tokenize(char *input, char delim);
cmd *append_cmd(cmd *head, char *cmdname, char **arguments);

/* env handling functions */
char **get_paths(void);
char *_getenv(char *var);

/* executor functions */
void executor(cmd *head);

/* utility functions */
int count_tokens(char *input, char delim);
int _strcmp(char *s1, char *s2);
char *_strcat(char *s1, char *s2);
char *_strdup(char *str);
void remove_nl(char *input);
void free_cmdlist(cmd *head);

/* test functions */
void print_cmd(cmd *head);
#endif
