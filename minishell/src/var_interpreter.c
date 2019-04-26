/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** var_interpreter
*/

#include <string.h>
#include <stdio.h>
#include "mysh.h"
#include "my.h"

char *get_variable(char *str, size_t *size)
{
	int i = 0;

	if (match(str, "$*") && !match(str, "${*")) {
		*size = strlen(str);
		return (&str[1]);
	} else if (match(str, "${*")) {
		str = &str[2];
		for (i = 0; str[i] && str[i] != '}'; i++);
		if (str[i] != '}') {
			dprintf(2, "Missing '}'.\n");
			return ((void *)-1);
		}
		str[i] = 0;
		*size = strlen(str) + 3;
		return (str);
	}
	*size = 1;
	return (NULL);
}

char *make_one_node(char *var, char **res, terminal_t *term)
{
	char *tmp = NULL;
	linked_list_t *list = NULL;
	char *env_val = NULL;

	if (var == NULL)
		return (NULL);
	else if (var == (void *)(-1))
		return ((void *)(-1));
	list = get_node(term->shell_vars, var);
	env_val = get_env_var_value(term->env, var);
	if (list == NULL && env_val == NULL) {
		my_free_array((void **)res);
		dprintf(2, "Variable not found.\n");
		return ((void *)-1);
	}
	if (list != NULL)
		tmp = ((shell_var_t *)list->element)->value;
	else
		tmp = env_val;
	return (tmp);
}

static char *get_word(char *current_word, char **res, terminal_t *term,\
char **new_str)
{
	char tmp[2] = {0, 0};
	char *var_val = NULL;
	char *var = NULL;
	size_t size = 0;

	if (new_str == NULL)
		return (NULL);
	for (int i = 0; current_word[i]; i += size) {
		var = get_variable(&current_word[i], &size);
		var_val = make_one_node(var, res, term);
		if (var_val == NULL) {
			tmp[0] = current_word[i];
			my_strdupcat(new_str, tmp);
			continue;
		}
		if (var_val == (void *)-1)
			return (NULL);
		my_strdupcat(new_str, var_val);
	}
	return (*new_str);
}

static char **get_new_cmd(parser_t *parser, terminal_t *term)
{
	char **res = calloc((size_t)parser->nb_nodes + 1, sizeof(*res));
	char *var = NULL;
	char *tmp = NULL;
	int index = 0;

	for (int i = 0; i < parser->nb_nodes; i++) {
		var = strdup("");
		tmp = get_word(parser->to_parse[i], res, term, &var);
		if (tmp == NULL && var != NULL) {
			free(var);
			return (NULL);
		}
		add_elem_to_array(&res, &index, parser->nb_nodes, var);
	}
	return (res);
}

int parse_vars(terminal_t *term, parser_t *parser)
{
	char **res = get_new_cmd(parser, term);

	if (res == NULL)
		return (1);
	my_free_array((void **)parser->to_parse);
	reset_parser(parser, my_array_len((void **)res));
	parser->to_parse = res;
	set_parser_types(parser);
	return (0);
}