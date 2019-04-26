/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** unset builtin
*/

/* File created the 24/05/2018 at 13:48:45 by julian.frabel@epitech.eu */

#include "my.h"
#include "mysh.h"
#include <stdlib.h>
#include <stdio.h>

void unset_if_needed(terminal_t *term, linked_list_t *node, char *patern)
{
	shell_var_t *shell_var = node->element;

	if (match(node->name, patern)) {
		free(shell_var->var);
		free(shell_var->value);
		free(shell_var);
		remove_node_by_name(&term->shell_vars, node->name);
	}
}

int builtin_unset(terminal_t *term, char **cmd_args)
{
	linked_list_t *node = NULL;
	linked_list_t *next = NULL;

	if (term == NULL || cmd_args == NULL)
		return (1);
	if (get_tab_size(cmd_args) == 1) {
		dprintf(2, UNSET_NEA);
		return (1);
	}
	for (int i = 1; cmd_args[i] != NULL; i++) {
		for (node = term->shell_vars; node != NULL; node = next) {
			next = node->next;
			unset_if_needed(term, node, cmd_args[i]);
		}
	}
	return (0);
}