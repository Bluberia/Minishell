/*
** EPITECH PROJECT, 2017
** Linked list
** File description:
** utils
*/

#include "linked_list.h"

linked_list_t *get_node_by_pos(int pos, linked_list_t *list)
{
	linked_list_t *cpy = list;

	for (int i = 0; i < pos && cpy; i++)
		cpy = cpy->next;
	return (cpy);
}