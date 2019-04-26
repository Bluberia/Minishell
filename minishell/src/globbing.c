/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** globbing
*/

#include <mysh.h>
#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <string.h>
#include "mysh.h"
#include "my.h"

static int make_glob(char ***res, int *index, parser_t *parser, int i)
{
	glob_t globber;
	int glob_res = glob(parser->to_parse[i],\
	GLOB_NOMAGIC | GLOB_TILDE_CHECK, NULL, &globber);

	if (glob_res == GLOB_NOMATCH && parser->types[i] == ARGUMENT) {
		dprintf(2, parser->to_parse[i]);
		dprintf(2, ": No match.\n");
		return (1);
	}
	if (globber.gl_pathc == 0 || parser->types[i] != ARGUMENT) {
		add_elem_to_array(res, index, parser->nb_nodes,\
		parser->to_parse[i]);
	} else {
		for (unsigned int i = 0; i < globber.gl_pathc; i++)
			add_elem_to_array(res, index, parser->nb_nodes,\
			globber.gl_pathv[i]);
	}
	return (0);
}

static void remake_parser(parser_t *parser, char **res)
{
	reset_parser(parser, my_array_len((void **)res));
	my_free_array((void **)parser->to_parse);
	parser->to_parse = res;
	set_parser_types(parser);
}

static int set_cmd_type(int *last_type, parser_t *parser, int i)
{
	if (parser->types[i] == COMMAND || parser->types[i] == BUILTIN)
		*last_type = parser->types[i];
	if (*last_type != COMMAND)
		return (1);
	return (0);
}

int make_globbing(parser_t *parser)
{
	char **res = calloc((size_t)parser->nb_nodes + 1, sizeof(*res));
	int index = 0;
	int last_cmd_type = COMMAND;

	if (res == NULL)
		return (1);
	for (int i = 0; i < parser->nb_nodes; i++) {
		if (set_cmd_type(&last_cmd_type, parser, i)) {
			add_elem_to_array(&res, &index, parser->nb_nodes,\
			parser->to_parse[i]);
			continue;
		}
		if (make_glob(&res, &index, parser, i) == 1) {
			my_free_array((void **)res);
			return (1);
		}
	}
	res[index] = 0;
	remake_parser(parser, res);
	return (0);
}