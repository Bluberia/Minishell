/*
** EPITECH PROJECT, 2018
** echo.c
** File description:
** Fonction for print what write the user
*/

#include "my.h"
#include "mysh.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

static int retype_the_same(char **cmd_args, int tab_size, int backslash)
{
	if (backslash == 0) {
		printf("%s", cmd_args[2]);
		for (int i = 3; i != tab_size; i++) {
			printf(" %s", cmd_args[i]);
		}
		fflush(stdout);
		return (0);
	}
	if (backslash == 1) {
		printf("%s", cmd_args[1]);
		for (int i = 2; i != tab_size; i++) {
			printf(" %s", cmd_args[i]);
		}
		fflush(stdout);
		my_putchar('\n');
		return (0);
	}
	return (0);
}

static int short_option_echo(char **cmd_args, int tab_size)
{
	if (tab_size == 2 && \
cmd_args[1][1] != 'n') {
		retype_the_same(cmd_args, tab_size, 1);
		return (0);
	}
	if (tab_size == 2 && \
cmd_args[1][1] == 'n')
		return (0);
	if (tab_size > 2 && \
cmd_args[1][1] == 'n') {
		retype_the_same(cmd_args, tab_size, 0);
		return (0);
	}
	return (0);
}

int command_echo(UNUSED terminal_t *term, char **cmd_args)
{
	int tab_size = get_tab_size(cmd_args);

	if (tab_size == 1) {
		my_putchar('\n');
		return (0);
	}
	if (tab_size > 1 && cmd_args[1][0] == '-') {
		short_option_echo(cmd_args, tab_size);
		return (0);
	}
	if (tab_size > 1) {
		retype_the_same(cmd_args, tab_size, 1);
		return (0);
	}
	return (0);
}
