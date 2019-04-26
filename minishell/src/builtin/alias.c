/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** Alias builtin
*/

#include <stdio.h>
#include <string.h>
#include "my.h"
#include "mysh.h"
#include "linked_list.h"

char *get_alias_str(linked_list_t *list, char *name)
{
	char *str = strdup("");
	linked_list_t *elem_l = get_node(list, name);

	if (elem_l == NULL || str == NULL)
		return (NULL);
	for (int i = 0; ((char **)elem_l->element)[i]; i++) {
		if (i > 0)
			my_strdupcat(&str, " ");
		my_strdupcat(&str, ((char **)elem_l->element)[i]);
	}
	return (str);
}

int display_alias(linked_list_t *list)
{
	char **arr = NULL;
	char *str = NULL;

	while (list) {
		arr = list->element;
		str = get_alias_str(list, list->name);
		if (my_array_len((void **)arr) > 1)
			printf("%s\t(%s)\n", list->name, str);
		else
			printf("%s\t%s\n", list->name, str);
		free(str);
		list = list->next;
	}
	return (1);
}

int display_one_alias(linked_list_t *list, char *name)
{
	if (get_node(list, name) == NULL)
		return (1);
	printf("%s\n", get_alias_str(list, name));
	return (1);
}

static int add_alias(char **cmd_args, linked_list_t *list,\
terminal_t **term)
{
	char **ncmd = calloc(my_array_len((void **)cmd_args) + 1,\
	sizeof(*ncmd));

	for (int i = 2; cmd_args[i]; i++)
		ncmd[i - 2] = strdup(cmd_args[i]);
	list = get_node((*term)->alias, cmd_args[1]);
	if (list == NULL)
		add_node(&(*term)->alias, cmd_args[1], ncmd);
	else {
		free(list->element);
		list->element = ncmd;
	}
	return (0);
}

int alias(terminal_t *term, char **cmd_args)
{
	linked_list_t *list = NULL;

	if (cmd_args == NULL)
		return (0);
	if (my_strcmp(cmd_args[0], "alias") == 0) {
		list = term->alias;
		if (my_array_len((void **) cmd_args) == 1)
			return (display_alias(list));
		else if (my_array_len((void **) cmd_args) == 2)
			return (display_one_alias(list, cmd_args[1]));
		add_alias(cmd_args, list, &term);
		return (1);
	}
	return (0);
}