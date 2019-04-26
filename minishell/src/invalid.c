/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** invalid
*/

#include <stdio.h>
#include "my.h"
#include "mysh.h"

int is_ambigous_redirection(parser_t *parser, int i)
{
	command_t cmd = parser->commands[i];

	if (cmd.has_redirection == 0)
		return (0);
	if (cmd.left_redirection > 1 || cmd.right_redirection > 1)
		return (1);
	if (cmd.has_pipe_before && cmd.left_redirection)
		return (1);
	if (cmd.has_pipe_after && cmd.right_redirection)
		return (1);
	return (0);
}

int is_double_pipe(parser_t *parser, int pos)
{
	if (!my_strcmp(parser->to_parse[pos], "|") && \
(pos + 1 == parser->nb_nodes || !my_strcmp(parser->to_parse[pos + 1], "|"))) {
		my_puterror(PIPE_NULL_COMMAND);
		return (1);
	}
	return (0);
}

int is_invalid_array(parser_t *parser)
{
	for (int i = 0; i < parser->nb_nodes; i++) {
		if (parser->types[i] == REDIRECT && \
(i + 1 == parser->nb_nodes || parser->types[i + 1] != REDIRECT_INFO)) {
			my_puterror(REDIRECT_MISSING_NAME);
			return (1);
		}
		if (is_double_pipe(parser, i))
			return (1);
	}
	for (int i = 0; parser->commands[i].arguments != NULL; i++) {
		if ((i == 0 && parser->commands[i].has_pipe_before) || \
(!(parser->commands[i + 1].arguments) && parser->commands[i].has_pipe_after)) {
			my_puterror(PIPE_NULL_COMMAND);
			return (1);
		} else if (is_ambigous_redirection(parser, i)) {
			my_puterror(REDIRECT_AMBIGOUS_OUTPUT);
			return (1);
		}
	}
	return (0);
}