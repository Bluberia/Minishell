/*
** EPITECH PROJECT, 2017
** minishell 1
** File description:
** cd home functions
*/

#include "my.h"
#include "mysh.h"
#include <unistd.h>

char *get_home_str(char ***env, char *path)
{
	char *home_var = get_env_var_value(*env, "HOME");
	char *result = NULL;

	if (home_var == NULL) {
		my_puterror(CD_HOME_NOT_FOUNT);
		return (NULL);
	}
	result = my_strdup(home_var);
	my_strdupcat(&result, &path[1]);
	return (result);
}

int move_to_home(terminal_t *term)
{
	char *home = get_env_var_value(term->env, "HOME");
	char *change_pwd = my_strdup("setenv PWD ");
	char *curr_path = NULL;

	if (home == NULL) {
		my_puterror(CD_HOME_NOT_FOUNT);
		return (1);
	}
	if (chdir(home) == -1) {
		my_puterror(home);
		my_puterror(CD_DIR_NOT_FOUNT);
		return (1);
	}
	curr_path = getcwd(curr_path, 0);
	my_strdupcat(&change_pwd, curr_path);
	free(curr_path);
	set_env(term, my_parse_str_to_array(change_pwd, " \t", "\"\'", "\"\'"));
	return (0);
}