/*
** EPITECH PROJECT, 2017
** minishell1_2017
** File description:
** main function
*/

#include "my.h"
#include "mysh.h"
#include <stdlib.h>

int main(int ac, char **av, char **env)
{
	char **cpy_env = duplicate_environment(env);

	(void)ac;
	(void)av;
	if (cpy_env == NULL)
		return (84);
	if (get_env_var_value(cpy_env, "PATH") == NULL) {
		set_env_var(&cpy_env, (char *[3]){"setenv", "PATH", \
"/usr/bin:/bin"});
	}
	return ((unsigned char)mysh(cpy_env));
}