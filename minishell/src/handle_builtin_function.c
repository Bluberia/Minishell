/*
** EPITECH PROJECT, 2017
** mysh
** File description:
** Run a builtin function if needed
*/

#include "my.h"
#include "mysh.h"

const builtin_t builtin[] = {
	{"cd", &command_cd},
	{"env", &display_environment},
	{"setenv", &set_env},
	{"unsetenv", &unset_env},
	{"alias", &alias},
	{"echo", &command_echo},
	{"history", &command_history},
	{"builtins", &builtin_builtins},
	{"set", &builtin_set},
	{"unset", &builtin_unset},
	{"chdir", &command_cd},
	{NULL, NULL}
};

int get_tab_size(char **tab)
{
	int tab_size = 0;

	for (int i = 0; tab[i] != NULL; i++) {
		tab_size++;
	}
	return (tab_size);
}

int handle_builtin(char **cmd_args, terminal_t *term)
{
	if (my_strncmp(cmd_args[0], "exit", 4) == 0)
		return (0);
	for (int i = 0; builtin[i].cmd_name != NULL; i++) {
		if (my_strcmp(builtin[i].cmd_name, cmd_args[0]) == 0)
			return (builtin[i].cmd_func(term, cmd_args));
	}
	return (-84);
}
