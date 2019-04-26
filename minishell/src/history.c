/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** history
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "my.h"
#include "mysh.h"

void add_history_elem(char *cmd, terminal_t *term)
{
	history_elem_t *elem = malloc(sizeof(*elem));
	time_t now = time(NULL);
	char time[6];

	if (elem == NULL)
		return;
	if (term->history != NULL && term->history->element != NULL)
		elem->id = ((history_elem_t *)term->history->element)->id + 1;
	else
		elem->id = 1;
	strftime(time, 6, "%H:%M", localtime(&now));
	elem->time = my_strdup(time);
	elem->cmd = my_strdup(cmd);
	add_node(&term->history, "command", elem);
}