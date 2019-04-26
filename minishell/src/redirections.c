/*
** EPITECH PROJECT, 2017
** PSU_minishell2
** File description:
** Redirections
*/

/* File created the 21/03/2018 at 16:09:35 by julian.frabel@epitech.eu */

#include <sys/types.h>
#include <sys/stat.h>
#include <linux/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "my.h"
#include "get_next_line.h"
#include "mysh.h"

int redirect_to_file_append(int pipe_fd[4], command_t *cmd)
{
	int fd = open(cmd->right_redirection_arg, \
O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	if (fd == -1) {
		my_perror(cmd->right_redirection_arg);
		return (1);
	}
	dup2(fd, pipe_fd[1]);
	dup2(pipe_fd[1], 1);
	return (0);
}

int redirect_to_file(int pipe_fd[4], command_t *cmd)
{
	int fd = open(cmd->right_redirection_arg, \
O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	if (fd == -1) {
		my_perror(cmd->right_redirection_arg);
		return (1);
	}
	dup2(fd, pipe_fd[1]);
	dup2(pipe_fd[1], 1);
	return (0);
}

int redirect_from_file(int *read_from, command_t *cmd)
{
	int fd = open(cmd->left_redirection_arg, O_RDONLY);

	if (fd == -1) {
		my_perror(cmd->left_redirection_arg);
		return (1);
	}
	*read_from = fd;
	return (0);
}

int redirect_from_stdin(int *read_from, command_t *cmd)
{
	int fd = open("./", O_RDWR | (__O_TMPFILE | O_DIRECTORY), \
S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	char *next_line = NULL;

	if (fd == -1) {
		my_perror("./");
		return (1);
	}
	dprintf((cmd->right_redirection) ? 2 : 1, "? ");
	next_line = get_next_line(0);
	while (my_strcmp(next_line, cmd->left_redirection_arg)) {
		write(fd, next_line, my_strlen(next_line));
		write(fd, "\n", 1);
		dprintf((cmd->right_redirection) ? 2 : 1, "? ");
		next_line = get_next_line(0);
	}
	lseek(fd, 0, SEEK_SET);
	*read_from = fd;
	return (0);
}

int setup_redirections(int pipe_fd[4], int *read_from, command_t *cmd)
{
	int ret = 0;

	if (cmd->has_redirection == 0)
		return (0);
	if (my_strcmp(cmd->right_redirection_type, ">>") == 0)
		ret += redirect_to_file_append(pipe_fd, cmd);
	if (my_strcmp(cmd->right_redirection_type, ">") == 0)
		ret += redirect_to_file(pipe_fd, cmd);
	if (my_strcmp(cmd->left_redirection_type, "<<") == 0)
		ret += redirect_from_stdin(read_from, cmd);
	if (my_strcmp(cmd->left_redirection_type, "<") == 0)
		ret += redirect_from_file(read_from, cmd);
	return (ret);
}