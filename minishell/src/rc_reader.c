/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** rc_reader
*/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include "my.h"
#include "mysh.h"

static char *get_path(char **env)
{
	char *home = get_env_var_value(env, "HOME");
	char *path = strdup("");

	if (path == NULL)
		return (NULL);
	if (home == NULL) {
		free(path);
		return (NULL);
	}
	my_strdupcat(&path, home);
	my_strdupcat(&path, "/.42rc");
	if (path == NULL)
		return (NULL);
	return (path);
}

static void run_rc(terminal_t *term, FILE *file)
{
	int return_value = 0;
	char *cmd = NULL;
	size_t size = 0;

	while (getline(&cmd, &size, file) != -1) {
		if (cmd[strlen(cmd) - 1] == '\n')
			cmd[strlen(cmd) - 1] = 0;
		run_line(cmd, term, &return_value);
		if (return_value != 0)
			break;
	}
	free(cmd);
}

void read_rc(char **env, terminal_t *term)
{
	char *path = get_path(env);
	FILE *file = NULL;
	int fd = 0;

	if (path == NULL)
		return;
	file = fopen(path, "r");
	if (file == NULL) {
		fd = open(path, O_CREAT, 0644);
		close(fd);
		return;
	}
	run_rc(term, file);
	fclose(file);
}
