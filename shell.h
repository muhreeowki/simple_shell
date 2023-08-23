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

/**
 * struct cmd - this is a struct to hold commands
 * @builtin: shows if command is builtin or not
 * @name: command name
 * @arguments: list of command args
 * @separator: separator after command
 * @function: function associated with command name (only for builtins)
 * @next: next command
 *
 */
typedef struct cmd
{
	int builtin;
	char *name;
	char **arguments;
	char *separator;
	int (*function)(char **args, char *name, int *count, int *status);
	struct cmd *next;
} cmd;

/* Global Variables */
extern char **environ;

/* main functions */
int user_mode(char **argv);
int file_mode(char **argv);

/* parser functions */
cmd *parser(char *input);
cmd *find_program(cmd *command, char **paths);
char **_strtok(char *input, char delim);
cmd *append_cmd(cmd *head, char *cmdname, char **arguments, char *sep);
int divide_sep(char *string, char **arguments_list,
	char **separators, char *substring, int *i, int *n);
char **tokenize(char *input);

/* env handling functions */
char **get_paths(void);
char *_getenv(char *var);

/* executor functions */
int executor(cmd *head, char **paths, char *name, int *count,
		int *exit_status);
int check_sep(char *prev_sep, int curr_state, int prev_state);
void execute_command(cmd *command, int *prev_status, int *curr_status);
int check_builtins(cmd *command);

/* utility functions */
ssize_t _getline(int fd, char **buff, size_t *size);
int handle_errors(char *message, int status);

/* string utility functions */
int count_tokens(char *input, char delim);
int _strcmp(char *s1, char *s2);
char *_strcat(char *s1, char *s2);
char *_strdup(char *str);
int _strlen(const char *s);
void remove_nl(char *input);
int check_empty(char *string);
int _atoi(char *s);
char *_itoa(int num, int base);
void reverse(char *string, int len);
char *_strcat2(char **strings);

/* memory management */
void free_cmdlist(cmd *head);
void handle_free(char *input, cmd *head, char **paths);
void free_all(char *input, char **lines,
		char *program_name, char *errmsg1, char *msg);
/* builtins functions */
int _cd(char **args, char *name, int *count, int *status);
int _exit2(char **args, char *name, int *count, int *status);
int _setenv(char **args, char *name, int *count, int *status);
int _unsetenv(char **args, char *name, int *count, int *status);
int _env(char **args, char *name, int *count, int *status);

/* test functions */
void print_cmd(cmd *head);
#endif
