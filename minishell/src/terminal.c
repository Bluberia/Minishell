/*
** EPITECH PROJECT, 2017
** 42SH
** File description:
** Terminal struct file
*/

#include <stdlib.h>
#include "my.h"
#include "mysh.h"

static void destroy_history_elem(linked_list_t *list)
{
	history_elem_t *elem = (history_elem_t *)list->element;

	free(elem->cmd);
	free(elem->time);
	free(list->element);
	free(list->name);
	free(list);
}

static void destroy_alias_elem(linked_list_t *list)
{
	free(list->name);
	free(list->element);
	free(list);
}

static void destroy_shell_var_elem(linked_list_t *list)
{
	shell_var_t *shell_var = list->element;

	if (shell_var != NULL) {
		free(shell_var->value);
		free(shell_var->var);
		free(shell_var);
	}
	free(list->name);
	free(list);
}

void destroy_struct(terminal_t *term)
{
	if (term->env != NULL)
		destroy_env(term->env);
	destroy_list(term->alias, &destroy_alias_elem);
	destroy_list(term->history, &destroy_history_elem);
	destroy_list(term->shell_vars, &destroy_shell_var_elem);
	free(term);
}

terminal_t *struct_init(char **env)
{
	terminal_t *term = malloc(sizeof(*term));

	if (term == NULL)
		return (NULL);
	term->alias = NULL;
	term->history = NULL;
	term->shell_vars = NULL;
	term->env = env;
	return (term);
}