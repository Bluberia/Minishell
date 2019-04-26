/*
** EPITECH PROJECT, 2017
** PSU_minishell2
** File description:
** Run a command line
*/

/* File created the 21/03/2018 at 13:59:06 by julian.frabel@epitech.eu */

#include "my.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "mysh.h"

int exec_cmd(parser_t *parser, terminal_t *term, int *return_value, int cmd)
{
	int child_exit_status = 0;

	if (my_exit(parser->commands[cmd].arguments, return_value))
		return (-10);
	if (parser->commands[cmd].is_builtin)
		return (handle_builtin(parser->commands[cmd].arguments, term));
	else {
		child_exit_status = run_cmd(term->env, \
parser->commands[cmd].arguments, parser->commands[cmd].has_pipe_after);
		return (child_exit_status);
	}
}

int close_and_reset_default(int pipe_fd[5], int *read_from, command_t *cmd)
{
	close(pipe_fd[1]);
	if (dup2(pipe_fd[3], 1) == -1) {
		my_perror("dup2");
		return (84);
	}
	if (dup2(pipe_fd[2], 0) == -1) {
		my_perror("dup2");
		return (84);
	}
	*read_from = (cmd->has_pipe_after) ? pipe_fd[0] : pipe_fd[2];
	return (0);
}

int setup_cmd_pipes(int pipe_fd[5], int read_from, command_t *cmd)
{
	int return_value = 0;

	if (pipe_fd[4] != -1)
		close(pipe_fd[4]);
	pipe_fd[4] = pipe_fd[0];
	if (pipe(pipe_fd) == -1) {
		my_perror("pipe");
		return (84);
	}
	if (setup_redirections(pipe_fd, &read_from, cmd) == 1)
		return_value = 85;
	if (dup2(read_from, 0) == -1) {
		my_perror("dup2");
		return (84);
	}
	if (cmd->has_pipe_after)
		if (dup2(pipe_fd[1], 1) == -1)
			return (84);
	return (return_value);
}

int close_all(int pipe_fd[5], int return_value)
{
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[2] != -1)
		close(pipe_fd[2]);
	if (pipe_fd[3] != -1)
		close(pipe_fd[3]);
	if (pipe_fd[4] != -1)
		close(pipe_fd[4]);
	return (return_value);
}

int run_commands(parser_t *parser, terminal_t *term, int *return_value)
{
	int pipe_fd[5] = {-1, -1, -1, -1, -1};
	int read_from = 0;
	int last = 0;
	int pipe_r = 0;
	command_t cmd = parser->commands[0];
	command_t last_cmd = EMPTY_CMD;

	pipe_fd[2] = dup(0);
	pipe_fd[3] = dup(1);
	for (int i = 1; cmd.arguments != NULL; i++) {
		pipe_r = setup_cmd_pipes(pipe_fd, read_from, &cmd);
		if (!pipe_r && (!(last_cmd.arguments) || (last_cmd.is_or && \
last) || (last_cmd.is_and && !last) || (!(last_cmd.is_or) && \
!(last_cmd.is_and))))
			last = exec_cmd(parser, term, return_value, i - 1);
		if (close_and_reset_default(pipe_fd, &read_from, &cmd))
			return (0);
		last_cmd = cmd;
		cmd = parser->commands[i];
	}
	return (close_all(pipe_fd, (pipe_r) ? pipe_r - 84 : last));
}