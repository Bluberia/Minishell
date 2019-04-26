/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** add_elem_to_array
*/

#include <stdlib.h>
#include <string.h>

void add_elem_to_array(char ***res, int *index, int nb, char *elem)
{
	if (*index >= nb)
		*res = realloc(*res, (*index + 2) * sizeof(*res));
	if (*res == NULL)
		return;
	(*res)[(*index)++] = strdup(elem);
	if ((*res)[(*index) - 1] == NULL)
		return;
	(*res)[*index] = 0;
}
