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

/* our structs */
typedef struct cmd
{
	int builtin;
	char *name;
	char **arguments;
	char *separator;
	void (*function)(char **arguments);
	struct cmd *next;
} cmd;

/* Global Variables */
extern char **environ;
extern cmd builtins[];

/* parser functions */
cmd *parser(char *input);
cmd *find_program(cmd *command, char **paths);
char **tokenize(char *input, char delim);
cmd *append_cmd(cmd *head, char *cmdname, char **arguments, char *sep);

/* env handling functions */
char **get_paths(void);
char *_getenv(char *var);

/* executor functions */
void executor(cmd *head, char **arguments);
int check_sep(char *sep, int curr_state, int prev_state);

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
