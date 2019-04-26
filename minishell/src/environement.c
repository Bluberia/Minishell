/*
** EPITECH PROJECT, 2017
** minishell1
** File description:
** Function that copy and restore the environement
*/

#include "my.h"
#include "mysh.h"
#include <stdlib.h>

char **duplicate_environment(char **env)
{
	int nb_env_var = 0;
	char **new_env = NULL;

	for (nb_env_var = 0; env[nb_env_var] != NULL; nb_env_var++);
	new_env = malloc(sizeof(*new_env) * (nb_env_var + 2));
	if (new_env == NULL)
		return (NULL);
	for (int i = 0; env[i] != NULL; i++) {
		new_env[i] = my_strdup(env[i]);
	}
	new_env[nb_env_var] = NULL;
	new_env[nb_env_var + 1] = NULL;
	return (new_env);
}

void destroy_env(char **env)
{
	for (int i = 0; env[i] != NULL; i++)
		free(env[i]);
	free(env);
}

int display_environment(terminal_t *term, char **cmd_args)
{
	(void)cmd_args;
	if (term == NULL || term->env == NULL)
		return (84);
	for (int i = 0; term->env[i] != NULL; i++) {
		my_printf("%s\n", term->env[i]);
	}
	return (0);
}

char **get_env_var(char **env, char *key)
{
	int key_len = my_strlen(key);

	if (env == NULL || key == NULL)
		return (NULL);
	for (int i = 0; env[i] != NULL; i++) {
		if (!my_strncmp(key, env[i], key_len) && env[i][key_len] == '=')
			return (&env[i]);
	}
	return (NULL);
}

char *get_env_var_value(char **env, char *key)
{
	int key_len = my_strlen(key);
	char *return_value = NULL;

	if (env == NULL || key == NULL)
		return (NULL);
	for (int i = 0; env[i] != NULL; i++) {
		if (!my_strncmp(key, env[i], key_len) && env[i][key_len] == '=')
			return_value = env[i];
	}
	if (return_value != NULL) {
		while (*return_value != '=' && *return_value != '\0')
			return_value++;
		if (*return_value == '=')
			return_value++;
	}
	return (return_value);
}