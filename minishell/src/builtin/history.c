/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** builtins historys
*/

#include "my.h"
#include "mysh.h"

int command_history(terminal_t *term, char **cmd_args)
{
	linked_list_t *cpy = term->history;
	history_elem_t *elem = NULL;
	int size = get_list_size(cpy);

	(void)cmd_args;
	for (int i = size - 1; i >= 0; i--) {
		elem = (history_elem_t *)get_node_by_pos(i, cpy)->element;
		my_printf("%6i\t%s\t%s\n", elem->id, elem->time, elem->cmd);
	}
	return (0);
}