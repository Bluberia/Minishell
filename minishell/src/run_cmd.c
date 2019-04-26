/*
** EPITECH PROJECT, 2017
** minishell 1
** File description:
** Run a command with the given path
*/

#include "my.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "mysh.h"
#include "signals_str.h"

void relativ_not_found(char *bin)
{
	char *error_msg = strerror(errno);

	if (strcmp(error_msg, "No such file or directory") == 0)
		dprintf(2, "%s: Command not found.\n", bin);
	else
		my_perror(bin);
}

void run_children(char **args, char **env)
{
	char *env_var_path = get_env_var_value(env, "PATH");
	char **cut_path = split_path(env_var_path);

	if (args != NULL && args[0] != NULL && my_str_contains(args[0], '/')) {
		if (execve(args[0], args, env) == -1)
			relativ_not_found(args[0]);
	} else {
		for (int i = 0; cut_path[i] != NULL; i++) {
			my_strdupcat(&(cut_path[i]), "/");
			my_strdupcat(&(cut_path[i]), args[0]);
			execve(cut_path[i], args, env);
		}
		dprintf(2, "%s: Command not found.\n", args[0]);
	}
	destroy_env(cut_path);
	get_next_line(-1);
	destroy_env(env);
	destroy_env(args);
	exit(-84);
}

void display_infos(int exit_status)
{
	if (WIFSIGNALED(exit_status)) {
		my_puterror(signals_str[WTERMSIG(exit_status) - 1]);
		if (WCOREDUMP(exit_status))
			my_puterror(" (core dumped)");
		my_puterror("\n");
	}
}

int run_parent(pid_t child_pid, int should_wait)
{
	int exit_status = 0;
	pid_t curr_pid = 0;
	int has_exit_error = 0;

	if (!should_wait)
		return (0);
	do {
		curr_pid = wait(&exit_status);
		display_infos(exit_status);
		if (WIFEXITED(exit_status) && WEXITSTATUS(exit_status) == \
(unsigned char)(-84))
			has_exit_error = 1;
	} while (curr_pid != child_pid);
	if (WIFEXITED(exit_status))
		return ((has_exit_error) ? 1 : WEXITSTATUS(exit_status));
	else if (WIFSIGNALED(exit_status))
		return (WTERMSIG(exit_status) + 128);
	else
		return (0);
}

int run_cmd(char **env, char **cmd_args, int has_pipe_after)
{
	pid_t child_pid = 0;
	int child_exit_status = 0;

	if (cmd_args == NULL || cmd_args[0] == NULL) {
		my_free_array((void **)cmd_args);
		return (0);
	}
	child_pid = fork();
	if (child_pid == 0) {
		run_children(cmd_args, env);
	} else {
		child_exit_status = run_parent(child_pid, !has_pipe_after);
		return (child_exit_status);
	}
	return (0);
}