/*
** EPITECH PROJECT, 2017
** minishell 1
** File description:
** Exit function
*/

#include "my.h"
#include "mysh.h"

int contains_only_num(char *arg)
{
	if (arg == NULL)
		return (1);
	for (int i = 0; arg[i] != '\0'; i++) {
		if (IS_NUM(arg[i]))
			continue;
		return (0);
	}
	return (1);
}

int my_exit(char **cmd_args, int *return_value)
{
	if (cmd_args == NULL)
		return (0);
	if (my_strcmp(cmd_args[0], "exit") == 0) {
		if (contains_only_num(cmd_args[1]) != 1 || \
get_tab_size(cmd_args) > 2) {
			my_puterror((IS_NUM(cmd_args[1][0])) ? \
EXIT_BAD_NB : EXIT_EXPRESSION_SYNTAX);
			return (0);
		}
		*return_value = my_getnbr(cmd_args[1]);
		if (*return_value == 0)
			*return_value = 256;
		return (1);
	}
	return (0);
}
