/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** set builtin
*/

/* File created the 24/05/2018 at 13:48:45 by julian.frabel@epitech.eu */

#include "my.h"
#include "mysh.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int is_var_valid(char *var)
{
	if (var == NULL)
		return (0);
	if (IS_ALPHA(var[0]) == 0) {
		my_puterror(SETENV_FIRST_ALPHA);
		return (0);
	}
	for (int i = 0; i < my_strlen(var); i++) {
		if (IS_ALPHA_NUMERICAL(var[i]))
			continue;
		my_puterror(SETENV_ONLY_ALPHA_NUM);
		return (0);
	}
	return (1);
}

int set_var(terminal_t *term, char *var, char *value)
{
	linked_list_t *shell_var_list = get_node(term->shell_vars, var);
	shell_var_t *shell_var = (shell_var_list) ? shell_var_list->element : 0;

	if (!is_var_valid(var))
		return (1);
	if (shell_var == NULL)
		shell_var = calloc(1, sizeof(*shell_var));
	if (shell_var == NULL)
		return (1);
	if (shell_var_list == NULL)
		shell_var->var = strdup(var);
	free(shell_var->value);
	if (value != NULL)
		shell_var->value = strdup(value);
	else
		shell_var->value = NULL;
	if (shell_var_list == NULL)
		add_node(&term->shell_vars, shell_var->var, shell_var);
	return (0);
}

int set_set_vars(terminal_t *term, char **cmd_args)
{
	int ret = 0;
	char **split_vars = NULL;

	if (cmd_args == NULL || term == NULL)
		return (1);
	for (int i = 1; !ret && cmd_args[i] != NULL; i++) {
		split_vars = my_parse_str_to_array(cmd_args[i], "=", "", "");
		if (split_vars) {
			ret = set_var(term, split_vars[0], split_vars[1]);
			my_free_array((void **)split_vars);
		}
	}
	return (ret);
}

void display_shell_var(terminal_t *term)
{
	linked_list_t *curr = term->shell_vars;
	shell_var_t *curr_var = NULL;

	if (term->history != NULL && term->history->next != NULL)
		printf("\t%s\n", \
((history_elem_t *)(term->history->next->element))->cmd);
	printf("\n");
	while (curr != NULL) {
		curr_var = curr->element;
		if (curr_var->var != NULL)
			printf("%s", curr_var->var);
		printf("\t");
		if (curr_var->value != NULL)
			printf("%s", curr_var->value);
		printf("\n");
		fflush(stdout);
		curr = curr->next;
	}
}

int builtin_set(terminal_t *term, char **cmd_args)
{
	int nb_args = get_tab_size(cmd_args);

	if (term == NULL || nb_args == 0)
		return (1);
	if (nb_args == 1) {
		display_shell_var(term);
		return (0);
	}
	return (set_set_vars(term, cmd_args));
}