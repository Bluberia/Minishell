/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** reset_parser
*/

#include <stdlib.h>
#include "mysh.h"

void reset_parser(parser_t *parser, int new_size)
{
	int *types = malloc(new_size * sizeof(*types));

	if (types == NULL)
		return;
	free(parser->types);
	parser->nb_nodes = new_size;
	parser->types = types;
}