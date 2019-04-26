/*
** EPITECH PROJECT, 2017
** minishell 1
** File description:
** cd builtin
*/

#include "my.h"
#include "mysh.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

void change_new_pwd(terminal_t *term)
{
	char *change_pwd = my_strdup("setenv PWD ");
	char *curr_path = NULL;
	char **cmd_args = NULL;

	curr_path = getcwd(NULL, 0);
	my_strdupcat(&change_pwd, curr_path);
	free(curr_path);
	cmd_args = my_parse_str_to_array(change_pwd, " \t", "\"\'", "\"\'");
	set_env(term, cmd_args);
	my_free_array((void **)cmd_args);
	free(change_pwd);
}

int move_to_dir(terminal_t *term, char *path)
{
	char *last_dir = get_env_var_value(term->env, "OLDPWD");

	if (my_strcmp(path, "-") == 0)
		path = last_dir;
	if (path[0] == '~')
		path = get_home_str(&term->env, path);
	if (chdir(path) == -1) {
		my_perror(path);
		return (1);
	}
	change_new_pwd(term);
	return (0);
}

void change_old_pwd(terminal_t *term, char *old_dir)
{
	char *change_pwd = my_strdup("setenv OLDPWD ");
	char **cmd_args = NULL;

	my_strdupcat(&change_pwd, old_dir);
	cmd_args = my_parse_str_to_array(change_pwd, " \t", "\"\'", "\"\'");
	set_env(term, cmd_args);
	my_free_array((void **)cmd_args);
	free(change_pwd);
}

int exec_cd(terminal_t *term, char **cmd_args)
{
	switch (get_tab_size(cmd_args))	{
	case 1: return (move_to_home(term));
	case 2: return (move_to_dir(term, cmd_args[1]));
	default: return (move_to_dir(term, cmd_args[2]));
	}
}

int command_cd(terminal_t *term, char **cmd_args)
{
	char *curr_dir = NULL;
	int return_value = 1;

	curr_dir = getcwd(curr_dir, 0);
	if (get_tab_size(cmd_args) > 2 && my_strcmp(cmd_args[1], "-p"))
		my_puterror(CD_TOO_MUCH_ARGS);
	else
		return_value = exec_cd(term, cmd_args);
	if (return_value == 0) {
		change_old_pwd(term, curr_dir);
		free(curr_dir);
		curr_dir = getcwd(NULL, 0);
		if (my_strcmp(cmd_args[1], "-p") == 0)
			my_printf("%s\n", curr_dir);
	}
	free(curr_dir);
	return (return_value);
}