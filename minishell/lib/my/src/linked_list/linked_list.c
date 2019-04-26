/*
** EPITECH PROJECT, 2017
** Lib my linked list
** File description:
** Add to linked list
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "linked_list.h"

void add_node(linked_list_t **list, char *name, void *element)
{
	linked_list_t *new_elem = malloc(sizeof(*new_elem));

	if (new_elem == NULL)
		return;
	new_elem->prev = NULL;
	new_elem->name = my_strdup(name);
	new_elem->element = element;
	new_elem->next = *list;
	if (*list != NULL)
		new_elem->next->prev = new_elem;
	*list = new_elem;
}

linked_list_t *get_node(linked_list_t *list, char *name)
{
	linked_list_t *copy = list;

	if (name == NULL)
		return (NULL);
	while (copy != NULL) {
		if (copy->name == NULL)
			continue;
		if (my_strcmp(copy->name, name) == 0)
			return (copy);
		copy = copy->next;
	}
	return (NULL);
}

void remove_node_by_name(linked_list_t **list, char *name)
{
	linked_list_t *node = get_node(*list, name);
	linked_list_t *prev_node = NULL;
	linked_list_t *next_node = NULL;

	if (node == NULL)
		return;
	prev_node = node->prev;
	next_node = node->next;
	if (prev_node)
		prev_node->next = next_node;
	else
		*list = next_node;
	if (next_node)
		next_node->prev = prev_node;
	free(node->name);
	free(node);
}

void destroy_list(linked_list_t *list, void (*destroyer)(linked_list_t *))
{
	linked_list_t *save = NULL;

	while (list) {
		save = list->next;
		destroyer(list);
		if (save == NULL)
			break;
		list = save;
	}
	list = NULL;
}

int get_list_size(linked_list_t *list)
{
	int size = 0;

	while (list) {
		size++;
		list = list->next;
	}
	return (size);
}