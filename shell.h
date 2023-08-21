#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <limits.h>
#include <fcntl.h>

#define MAX_INPUT_SIZE 4096

/* our structs */
typedef struct cmd
{
	int builtin;
	char *name;
	char **arguments;
	char *separator;
	int (*function)(char **args);
	struct cmd *next;
} cmd;

/* Global Variables */
extern char **environ;

/* main functions */
int user_mode(void);
int file_mode(char **argv);

/* parser functions */
cmd *parser(char *input);
cmd *find_program(cmd *command, char **paths);
char **tokenize(char *input, char delim);
cmd *append_cmd(cmd *head, char *cmdname, char **arguments, char *sep);

/* env handling functions */
char **get_paths(void);
char *_getenv(char *var);
int _env(char **args);

/* executor functions */
void executor(cmd *head, char **arguments);
int check_sep(char *sep, int curr_state, int prev_state);
void execute_command(cmd *command, int *prev_status, int *curr_status);
cmd *init_builtins(void);

/* utility functions */
ssize_t _getline(int fd, char **buff, size_t *size);
int handle_errors(char *message);

/* string utility functions */
int count_tokens(char *input, char delim);
int _strcmp(char *s1, char *s2);
char *_strcat(char *s1, char *s2);
char *_strdup(char *str);
int _strlen(const char *s);
void remove_nl(char *input);
int check_empty(char *string);
int _atoi(char *s);

/* memory management */
void free_cmdlist(cmd *head);
void handle_free(char *input, cmd *head, char **paths);

/* builtins functions */
int _cd(char **args);
int _exit2(char **args);
int _setenv(char **args);
int _unsetenv(char **args);

/* test functions */
void print_cmd(cmd *head);
#endif
