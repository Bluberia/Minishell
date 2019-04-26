/*
** EPITECH PROJECT, 2017
** PSU_minishell2
** File description:
** Parse a command to the parser
*/

/* File created the 20/03/2018 at 18:09:05 by julian.frabel@epitech.eu */

#include "my.h"
#include <stdlib.h>
#include "mysh.h"

void fill_redirect(command_t *curr_cmd, parser_t *parser, int pos_in_parser)
{
	char *redirect = parser->to_parse[pos_in_parser];

	curr_cmd->has_redirection += 1;
	if (redirect[0] == '<') {
		curr_cmd->left_redirection += 1;
		if (curr_cmd->left_redirection == 1)
			curr_cmd->left_redirection_type = my_strdup(redirect);
		if (curr_cmd->left_redirection_arg != NULL)
			free(curr_cmd->left_redirection_arg);
		curr_cmd->left_redirection_arg = NULL;
	} else {
		curr_cmd->right_redirection += 1;
		if (curr_cmd->right_redirection == 1)
			curr_cmd->right_redirection_type = my_strdup(redirect);
		if (curr_cmd->right_redirection_arg != NULL)
			free(curr_cmd->right_redirection_arg);
		curr_cmd->right_redirection_arg = NULL;
	}
}

void fill_redirect_info(command_t *curr_cmd, parser_t *parser, \
int pos_in_parser)
{
	char *arg = my_strdup(parser->to_parse[pos_in_parser]);

	if (parser->to_parse[pos_in_parser - 1][0] == '<') {
		curr_cmd->left_redirection_arg = arg;
	} else {
		curr_cmd->right_redirection_arg = arg;
	}
}

void fill_argument(command_t *curr_cmd, parser_t *parser, \
int pos_in_parser, int *curr_arg)
{
	int type = parser->types[pos_in_parser];

	if (type == ARGUMENT) {
		curr_cmd->arguments[*curr_arg] = \
my_strdup(parser->to_parse[pos_in_parser]);
		(*curr_arg) = (*curr_arg) + 1;
	} else if (type == BUILTIN || type == COMMAND) {
		curr_cmd->arguments[0] = \
my_strdup(parser->to_parse[pos_in_parser]);
	}
	if (type == BUILTIN)
		curr_cmd->is_builtin = true;
	if (type == COMMAND)
		curr_cmd->is_builtin = false;
}

int set_after_token(int pos, parser_t *parser, command_t *cmd)
{
	bool is_out_of_bound = ((pos < 0) || (pos >= parser->nb_nodes));

	cmd->has_pipe_after = (!is_out_of_bound && \
(!my_strcmp("|", parser->to_parse[pos])));
	cmd->is_and = (!is_out_of_bound && \
(!my_strcmp("&&", parser->to_parse[pos])));
	cmd->is_or = (!is_out_of_bound && \
(!my_strcmp("||", parser->to_parse[pos])));
	return (!is_out_of_bound && (!my_strcmp("|", parser->to_parse[pos])));
}

void fill_command(parser_t *parser, int start, int nb_cmd)
{
	int nb_args = get_cmd_nb_args(parser, start);
	int curr_arg = 1;
	int i = start;
	command_t *curr_cmd = &(parser->commands[nb_cmd]);

	curr_cmd->arguments = malloc(sizeof(char *) * (nb_args + 2));
	if (curr_cmd->arguments == NULL)
		return;
	curr_cmd->has_pipe_before = set_after_token(i - 1, parser, curr_cmd);
	for (; i < parser->nb_nodes && parser->types[i] != TOKEN; i++)
		if (parser->types[i] == REDIRECT)
			fill_redirect(curr_cmd, parser, i);
		else if (parser->types[i] == REDIRECT_INFO)
			fill_redirect_info(curr_cmd, parser, i);
		else
			fill_argument(curr_cmd, parser, i, &curr_arg);
	curr_cmd->arguments[curr_arg] = NULL;
	set_after_token(i, parser, curr_cmd);
}