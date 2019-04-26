/*
** EPITECH PROJECT, 2017
** minishell 1
** File description:
** Set a new environment var or update it
*/

#include "my.h"
#include "mysh.h"
#include <stdlib.h>

int is_key_valid(char *key)
{
	if (key == NULL)
		return (0);
	if (IS_ALPHA(key[0]) == 0) {
		my_puterror(SETENV_FIRST_ALPHA);
		return (0);
	}
	for (int i = 0; i < my_strlen(key); i++) {
		if (IS_ALPHA_NUMERICAL(key[i]))
			continue;
		my_puterror(SETENV_ONLY_ALPHA_NUM);
		return (0);
	}
	return (1);
}

int set_env_var(char ***env, char **cmd_args)
{
	char **env_var = get_env_var(*env, cmd_args[1]);
	char *new_var = my_strdup(cmd_args[1]);
	char **new_env = NULL;

	my_strdupcat(&new_var, "=");
	my_strdupcat(&new_var, cmd_args[2]);
	if (env_var != NULL) {
		free(*env_var);
		*env_var = new_var;
	} else {
		new_env = duplicate_environment(*env);
		destroy_env(*env);
		*env = new_env;
		(*env)[get_tab_size(*env)] = new_var;
	}
	return (0);
}

int set_env(terminal_t *term, char **cmd_args)
{
	int nb_args = get_tab_size(cmd_args);

	if (term == NULL || term->env == NULL || nb_args == 0)
		return (1);
	if (nb_args == 1)
		display_environment(term, cmd_args);
	if (nb_args > 3) {
		my_puterror(SETENV_TOO_MUCH_ARGS);
		return (1);
	}
	if (is_key_valid(cmd_args[1]))
		return (set_env_var(&term->env, cmd_args));
	return (1);
}