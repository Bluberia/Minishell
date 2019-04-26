/*
** EPITECH PROJECT, 2017
** PSU_minishell2
** File description:
** Destroy and free a parser object
*/

/* File created the 21/03/2018 at 14:55:11 by julian.frabel@epitech.eu */

#include <stdlib.h>
#include "my.h"
#include "mysh.h"

void destroy_parser(parser_t *parser)
{
	my_free_array((void **)parser->to_parse);
	free(parser->types);
	for (int i = 0; parser->commands[i].arguments; i++) {
		my_free_array((void **)parser->commands[i].arguments);
		free(parser->commands[i].left_redirection_type);
		free(parser->commands[i].left_redirection_arg);
		free(parser->commands[i].right_redirection_type);
		free(parser->commands[i].right_redirection_arg);
	}
	free(parser->commands);
}