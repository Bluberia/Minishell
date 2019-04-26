/*
** EPITECH PROJECT, 2017
** minishell 1
** File description:
** mysh core function
*/

#include "my.h"
#include "mysh.h"
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void destroy_sh(char *command, terminal_t *term)
{
	free(command);
	if (term)
		destroy_struct(term);
	get_next_line(-1);
}

void ctrl_c_handler(int signal_nb)
{
	(void)signal_nb;
	my_printf("\b\b  \b\b\n");
	display_prompt();
}

void ctrl_z_handler(int signal_nb)
{
	(void)signal_nb;
	my_printf("\b\b  \b\b");
}

void connect_signals(void)
{
	signal(SIGINT, &ctrl_c_handler);
	signal(SIGTSTP, &ctrl_z_handler);
}

int mysh(char **env)
{
	char *command = NULL;
	int return_value = 0;
	int line = 0;
	terminal_t *term = struct_init(env);

	connect_signals();
	do {
		display_prompt();
		command = get_next_line(0);
		if (command != NULL && term != NULL)
			line = run_line(command, term, &return_value);
		if (return_value != 0)
			break;
		free(command);
	} while (command != NULL);
	if (isatty(0))
		my_printf("exit\n");
	destroy_sh(command, term);
	return ((return_value != 0) ? return_value : line);
}