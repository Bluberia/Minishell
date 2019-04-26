/*
** EPITECH PROJECT, 2017
** PSU_minishell2
** File description:
** Create the command array and fill it
*/

/* File created the 20/03/2018 at 16:52:49 by julian.frabel@epitech.eu */

#include "my.h"
#include <stdlib.h>
#include "mysh.h"

int get_nb_commands(parser_t *parser)
{
	int nb_commands = 0;

	for (int i = 0; i < parser->nb_nodes; i++) {
		if (parser->types[i] == COMMAND || parser->types[i] == BUILTIN)
			nb_commands++;
	}
	return (nb_commands);
}

int get_cmd_nb_args(parser_t *parser, int start)
{
	int nb_args = 0;
	int nb_nodes = parser->nb_nodes;

	for (int i = start; i < nb_nodes && parser->types[i] != TOKEN; i++) {
		if (parser->types[i] == ARGUMENT)
			nb_args++;
	}
	return (nb_args);
}

int set_parser_commands(parser_t *parser)
{
	int nb_cmd = get_nb_commands(parser);
	int type = 0;
	int curr_cmd_nb = 0;

	parser->commands = malloc(sizeof(*(parser->commands)) * (nb_cmd + 1));
	if (parser->commands == NULL)
		return (84);
	for (int i = 0; i < parser->nb_nodes; i++) {
		type = parser->types[i];
		if (i == 0 || (type == TOKEN && (i + 1 < parser->nb_nodes))) {
			parser->commands[curr_cmd_nb] = EMPTY_CMD;
			fill_command(parser, i + (i != 0), curr_cmd_nb);
			curr_cmd_nb++;
		}
	}
	parser->commands[nb_cmd] = EMPTY_CMD;
	return (0);
}