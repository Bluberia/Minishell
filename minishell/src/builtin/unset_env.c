/*
** EPITECH PROJECT, 2017
** minishell 1
** File description:
** Unset an environment var
*/

#include "my.h"
#include "mysh.h"
#include <stdlib.h>
#include <stdio.h>

void remove_env_var(char ***env, char **env_var)
{
	int i = 0;

	for (i = 0; ((*env)[i] != *env_var) && (*env)[i] != NULL; i++);
	free((*env)[i]);
	for (i = i + 1; (*env)[i] != NULL; i++) {
		(*env)[i - 1] = (*env)[i];
	}
	(*env)[i - 1] = NULL;
}

char **get_vars(char **env, char *patern)
{
	int key_len = my_strlen(patern);
	char **vars = NULL;
	int nb_match = 0;
	int pos_in_vars = 0;
	char *key = malloc(sizeof(*key) * (key_len + 3));

	if (env == NULL || patern == NULL || key == NULL)
		return (NULL);
	key = my_strcpy(key, patern);
	key = my_strcat(key, "=*");
	for (int i = 0; env[i] != NULL; i++)
		if (match(env[i], key))
			nb_match++;
	vars = malloc(sizeof(*vars) * (nb_match + 1));
	vars[nb_match] = NULL;
	for (int i = 0; env[i] != NULL; i++)
		if (match(env[i], key))
			vars[pos_in_vars++] = env[i];
	free(key);
	return (vars);
}

int unset_env(terminal_t *term, char **cmd_args)
{
	char **env_var = NULL;

	if (cmd_args == NULL)
		return (1);
	if (get_tab_size(cmd_args) == 1) {
		dprintf(2, UNSETENV_NEA);
		return (1);
	}
	for (int i = 1; cmd_args[i] != NULL; i++) {
		env_var = get_vars(term->env, cmd_args[i]);
		for (int j = 0; env_var != NULL && env_var[j] != NULL; j++) {
			remove_env_var(&term->env, &env_var[j]);
		}
		if (env_var)
			free(env_var);
	}
	return (0);
}