/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** new_alias
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "my.h"
#include "mysh.h"

bool alias_loop(char *current, linked_list_t **list)
{
	linked_list_t *copy = *list;

	if (*list && strcmp(current, (*list)->name) == 0)
		return (false);
	if (get_node(*list, current) != NULL) {
		while (copy) {
			free(copy->name);
			copy = copy->next;
		}
		return (true);
	}
	add_node(list, current, NULL);
	return (false);
}

char **get_alias(terminal_t *term, char *arg, int type)
{
	linked_list_t *alist = NULL;
	linked_list_t *current = get_node(term->alias, arg);
	linked_list_t *tmp = NULL;
	char **to_concat = NULL;

	if (type != COMMAND && type != BUILTIN)
		return (NULL);
	while (current != NULL && strcmp(current->name, arg) == 0) {
		if (tmp != NULL && strcmp(tmp->name, arg) == 0)
			break;
		if (alias_loop(get_node(term->alias, arg)->name, &alist)) {
			dprintf(2, "Alias loop.\n");
			return ((void *) -1);
		}
		to_concat = current->element;
		arg = ((char **)current->element)[0];
		tmp = current;
		current = get_node(term->alias, arg);
	}
	return (to_concat);
}

void make_alias(char ***res, int *index, char **alias, int size)
{
	if (alias == NULL)
		return;
	for (int i = 0; alias[i]; i++)
		add_elem_to_array(res, index, size, alias[i]);
}

static void new_parser(parser_t *parser, char **res)
{
	my_free_array((void **)parser->to_parse);
	reset_parser(parser, my_array_len((void **)res));
	parser->to_parse = res;
	set_parser_types(parser);
}

int exec_all_alias(parser_t *parser, terminal_t *term)
{
	char **res = calloc((size_t)parser->nb_nodes + 1, sizeof(*res));
	int index = 0;
	char **alias = NULL;

	if (res == NULL)
		return (0);
	for (int i = 0; i < parser->nb_nodes; i++) {
		alias = get_alias(term, parser->to_parse[i], parser->types[i]);
		if (alias == NULL) {
			add_elem_to_array(&res, &index, parser->nb_nodes,\
			parser->to_parse[i]);
			continue;
		}
		if (alias == (void *)(-1))
			return (0);
		make_alias(&res, &index, alias, parser->nb_nodes);
	}
	new_parser(parser, res);
	return (1);
}