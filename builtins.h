#ifndef BUILTINS
#define BUILTINS
	cmd builtins[7] = {
		{0, "cd", NULL, NULL, _cd, NULL},
		{0, "env", NULL, NULL, _env, NULL},
		{0, "setenv", NULL, NULL, _setenv, NULL},
		{0, "unsetenv", NULL, NULL, _unsetenv, NULL},
		{0, "exit", NULL, NULL, _exit2, NULL},
		{0, "alias", NULL, NULL, NULL, NULL},
		{0, NULL, NULL, NULL, NULL, NULL}
	}; 
#endif
