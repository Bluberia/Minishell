/*
** EPITECH PROJECT, 2017
** PSU_minishell2
** File description:
** Set the types in the parser
*/

/* File created the 20/03/2018 at 14:39:13 by julian.frabel@epitech.eu */

#include "my.h"
#include "mysh.h"

int modify_token(int to_return, bool *was_redirect, bool *is_in_cmd)
{
	if (*was_redirect) {
		to_return = REDIRECT_INFO;
		*was_redirect = false;
	}
	*was_redirect = (to_return == REDIRECT);
	if (to_return == TOKEN)
		*is_in_cmd = false;
	if (*is_in_cmd && to_return == BUILTIN)
		to_return = ARGUMENT;
	if (to_return == BUILTIN || to_return == COMMAND)
		*is_in_cmd = true;
	return (to_return);
}

int get_type_from(node_parser_t *infos, char *arg, bool *is_in_cmd)
{
	char **args = NULL;
	int to_return = 0;
	static bool was_redirect = false;

	for (int i = 0; infos[i].strings != NULL; i++) {
		args = my_parse_str_to_array(infos[i].strings, ",", "[", "]");
		for (int j = 0; args[j] != NULL; j++) {
			to_return = (!my_strcmp(arg, args[j])) ? \
infos[i].type : to_return;
		}
		my_free_array((void **)args);
	}
	to_return = modify_token(to_return, &was_redirect, is_in_cmd);
	return (to_return);
}

void set_parser_types(parser_t *parser)
{
	int i = 0;
	bool is_in_cmd = false;

	if (parser == NULL || parser->parsing_infos == NULL || \
parser->to_parse == NULL || parser->types == NULL)
		return;
	for (i = 0; parser->to_parse[i] != NULL; i++) {
		parser->types[i] = get_type_from(parser->parsing_infos, \
parser->to_parse[i], &is_in_cmd);
		if (i && parser->types[i - 1] == 4 && parser->types[i] != TOKEN)
			parser->types[i] = REDIRECT_INFO;
		if (!is_in_cmd && parser->types[i] == ARGUMENT) {
			parser->types[i] = COMMAND;
			is_in_cmd = true;
		}
	}
	for (i--; i > 0; i--)
		if (parser->types[i - 1] == BUILTIN && parser->types[i] == 3)
			parser->types[i] = ARGUMENT;
}