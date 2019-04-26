/*
** EPITECH PROJECT, 2017
** PSU_minishell2
** File description:
** Run a function, return -10 if should exit
*/

/* File created the 20/03/2018 at 13:00:30 by julian.frabel@epitech.eu */

#include "my.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "mysh.h"

static int pre_run_line(char *command, terminal_t *term, parser_t *parser)
{
	add_history_elem(command, term);
	free(command);
	set_parser_types(parser);
	if (!exec_all_alias(parser, term))
		return (0);
	if (parse_vars(term, parser))
		return (0);
	if (make_globbing(parser) == 1)
		return (0);
	set_parser_commands(parser);
	if (is_invalid_array(parser)) {
		destroy_parser(parser);
		return (0);
	}
	return (1);
}

int run_line(char *command, terminal_t *term, int *return_value)
{
	node_parser_t info[] = {{TOKEN, PARSER_TOKEN},\
	{BUILTIN, PARSER_BUILTIN}, {REDIRECT, PARSER_REDIRECT}, {-1, NULL}};
	command = isolate_tokens(&command, PARSER_ISOLATE, "\"\'", "\"\'");
	char **parsed = my_parse_str_to_array(command, " \t", "\"\'", "\"\'");
	int *types = malloc(my_array_len((void **)parsed) * sizeof(*types));
	parser_t parser = {my_array_len((void **)parsed), \
info, parsed, types, NULL};
	int function_return = 0;

	if (types == NULL) {
		free(command);
		return (1);
	}
	if (!pre_run_line(command, term, &parser))
		return (1);
	function_return = run_commands(&parser, term, return_value);
	destroy_parser(&parser);
	return (function_return);
}