/*
** EPITECH PROJECT, 2017
** minishell1
** File description:
** Display a prompt when asked
*/

#include "my.h"
#include "mysh.h"
#include <unistd.h>

int get_slash(char *str)
{
	int last_slash = 0;

	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == '/')
			last_slash = i;
	}
	return (last_slash);
}

void display_prompt(void)
{
	char *path = NULL;
	char *curr_folder = NULL;

	if (isatty(0) == 0)
		return;
	path = getcwd(path, 0);
	curr_folder = (get_slash(path)) ? &path[get_slash(path) + 1] : path;
	my_printf("%s> ", (curr_folder != NULL) ? curr_folder : "ERROR");
	if (path)
		free(path);
}